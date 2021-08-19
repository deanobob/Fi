/// @file allegro_render_controller.cpp

#ifndef CI

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"
#include "plog/Log.h"
#include "allegro_render_controller.hpp"

namespace render
{
    allegro_render_controller::allegro_render_controller(ALLEGRO_EVENT_QUEUE* p_event_queue)
        : mp_event_queue(p_event_queue)
    {
        al_init();

        mp_event_queue = p_event_queue ? p_event_queue : al_create_event_queue();
    }

    bool allegro_render_controller::initialise()
    {
        if (!al_init_image_addon())
        {
            PLOG_ERROR << "Failed to initialise image addon";
            return false;
        }

        if (!al_init_font_addon())
        {
            PLOG_ERROR << "Failed to initialise font addon";
            return false;
        }

        if (!al_init_ttf_addon())
        {
            PLOG_ERROR << "Failed to initialise ttf addon";
            return false;
        }

        if (!al_init_primitives_addon())
        {
            PLOG_ERROR << "Failed to initialise primitives addon";
            return false;
        }

        return true;
    }

    void allegro_render_controller::process_events()
    {
        ALLEGRO_EVENT event;

        while (al_get_next_event(mp_event_queue, &event))
        {
            switch (event.type)
            {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_display_close();
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_display_gained_focus();
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_display_lost_focus();
                    }
                    break;
                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                    al_acknowledge_resize(mp_display);

                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_display_resize(event.display.width, event.display.height);
                    }

                    break;
                default:
                    PLOG_DEBUG << "Unknown event" << event.type;
                    break;
            }
        }
    }

    bool allegro_render_controller::create_window(const window_properties& properties)
    {
        // Define flags based on properties configuration
        int flags{0};
        if (properties.fullscreen)
        {
            flags |= ALLEGRO_FULLSCREEN_WINDOW;
        }

        if (properties.resizeable)
        {
            flags |= ALLEGRO_RESIZABLE;
        }

        al_set_new_display_flags(flags);

        if (properties.vsync)
        {
            // Enable vsync
            al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
        }

        if (properties.msaa_enabled)
        {
            // Turning multisampling on
            al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
            al_set_new_display_option(ALLEGRO_SAMPLES, properties.msaa_samples, ALLEGRO_SUGGEST);
        }

        mp_display = al_create_display(properties.width, properties.height);
        if (mp_display == nullptr)
        {
            PLOG_ERROR << "Failed to load display";
            return false;
        }
        else
        {
            al_set_window_title(mp_display , properties.title.c_str());

            mp_target = al_create_bitmap(properties.width, properties.height);

            if (mp_display)
            {
                al_register_event_source(mp_event_queue, al_get_display_event_source(mp_display));

                for (auto& listener_iter : mp_event_listeners)
                {
                    listener_iter->on_display_resize(properties.width, properties.height);
                }
            }
        }

        return true;
    }

    void allegro_render_controller::set_clear_color(const utilities::color& color)
    {
        m_clear_color = al_map_rgb(color.r, color.g, color.b);
    }

    void allegro_render_controller::clear()
    {
        al_clear_to_color(m_clear_color);
    }

    void allegro_render_controller::set_transform(const transform& transform)
    {
        ALLEGRO_TRANSFORM al_transform;
        al_identity_transform(&al_transform);
        al_translate_transform(&al_transform,
            transform.viewport.x + (transform.viewport.width / -2),
            transform.viewport.y + (transform.viewport.height / -2));
        al_rotate_transform(&al_transform, transform.rotation);
        al_translate_transform(&al_transform,
            (transform.viewport.width / 2),
            (transform.viewport.height / 2));
        al_scale_transform(&al_transform, transform.scale.x, transform.scale.y);
        al_use_transform(&al_transform);

        al_set_clipping_rectangle(static_cast<int>(transform.viewport.x),
                                  static_cast<int>(transform.viewport.y),
                                  static_cast<int>(transform.viewport.width),
                                  static_cast<int>(transform.viewport.height));
    }

    bool allegro_render_controller::load_bitmap(
        const std::string& filename,
        const utilities::vector2& position,
        const utilities::vector2& size,
        uint32_t& bitmap_id)
    {
        ALLEGRO_BITMAP* p_parent_bitmap{nullptr};

        const auto& iter = m_bitmap_cache.find(filename);
        if (iter != m_bitmap_cache.end())
        {
            p_parent_bitmap = iter->second;
        }
        else // load parent bitmap and save it in m_bitmap_cache
        {
            const std::string full_path = get_assets_path() + filename;
            p_parent_bitmap = al_load_bitmap(full_path.c_str());
            if (p_parent_bitmap != nullptr)
            {
              m_bitmap_cache[filename] = p_parent_bitmap;
            }
            else
            {
                PLOG_ERROR << "Failed to load file " << full_path.c_str() << " " << al_get_errno();
                return false;
            }
        }

        ALLEGRO_BITMAP* p_sub_bitmap = al_create_sub_bitmap(
            p_parent_bitmap,
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.x),
            static_cast<int>(size.y));
        if (p_sub_bitmap != nullptr)
        {
            // assign m_next_sprite_id to bitmap_id and save sub bitmap in sprite cache
            bitmap_id = m_next_sprite_id++;
            m_sprite_cache[bitmap_id] = p_sub_bitmap;
        }
        else
        {
            PLOG_ERROR << "Failed to load sub bitmap for file " << filename.c_str();
            return false;
        }

        return true;
    }

    bool allegro_render_controller::load_font(
        const std::string& filename,
        uint32_t font_size,
        uint32_t flags,
        uint32_t& font_id)
    {
        // Generate font unique name (combination of font name and font size)
        const std::string font_unique_name = filename + std::to_string(font_size);

        // Try and obtain ID of pre-loaded font by searching for fontUID
        const auto& font_iter = m_font_ids.find(font_unique_name);
        if (font_iter != m_font_ids.end())
        {
            font_id = font_iter->second;
            return true;
        }

        // Font wasn't found so load it
        const std::string full_path = get_assets_path() + filename;
        ALLEGRO_FONT* p_font = al_load_ttf_font(full_path.c_str(), font_size, flags);
        if (p_font != nullptr)
        {
            // Store font in cache mapped to font Id
            font_id = m_next_font_id++;
            m_font_cache[font_id] = p_font;
            // Store font ID against font unique name allowing for reuse
            m_font_ids[font_unique_name] = font_id;
        }
        else
        {
            PLOG_ERROR << "Failed to load font from file " << full_path.c_str();
            return false;
        }

        return true;
    }

    void allegro_render_controller::render_bitmap(
        uint32_t bitmap_id,
        const utilities::vector2& position,
        uint32_t flags)
    {
        ALLEGRO_BITMAP* p_bitmap = get_bitmap(bitmap_id);
        if (p_bitmap != nullptr)
        {
            al_draw_bitmap(p_bitmap, position.x, position.y, flags);
        }
    }

    void allegro_render_controller::render_fill_rect(const utilities::rectangle& rect, const utilities::color& color)
    {
      ALLEGRO_COLOR al_color = al_map_rgba(color.r, color.g, color.b, color.a);

      al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.width,
          rect.y + rect.height, al_color);
    }

    void allegro_render_controller::render_draw_line(
        const float x1, 
        const float y1, 
        const float x2,
        const float y2, 
        const utilities::color& color,
        float thickness)
    {
        ALLEGRO_COLOR al_color{};
        al_color.r = color.r;
        al_color.g = color.g;
        al_color.b = color.b;
        al_color.a = color.a;

        al_draw_line(x1, y1, x2, y2, al_color, thickness);
    }

    void allegro_render_controller::render_text(
        const uint32_t m_font_id,
        const std::string& text,
        const float x,
        const float y,
        const utilities::color& color,
        const uint32_t flags)
    {
        const auto& font_iter = m_font_cache.find(m_font_id);
        if (font_iter == m_font_cache.end())
        {
            return;
        }

        const ALLEGRO_FONT* p_font = font_iter->second;
        if (p_font != nullptr)
        {
            al_draw_text(
                p_font,
                al_map_rgba(color.r, color.g, color.b, color.a),
                x,
                y,
                flags,
                text.c_str());
        }
    }

    void allegro_render_controller::flip()
    {
        al_flip_display();
    }

    void allegro_render_controller::destroy_window()
    {
        if (mp_target != nullptr)
        {
            al_destroy_bitmap(mp_target);
            mp_target = nullptr;
        }

        if (mp_event_queue != nullptr)
        {
            al_unregister_event_source(mp_event_queue, al_get_display_event_source(mp_display));
            mp_event_queue = nullptr;
        }

        if (mp_display  != nullptr)
        {
            al_destroy_display(mp_display);
            mp_display  = nullptr;
        }

        for (auto& iter : m_sprite_cache)
        {
            al_destroy_bitmap(iter.second);
        }
        m_sprite_cache.clear();

        for (auto& iter : m_bitmap_cache)
        {
            al_destroy_bitmap(iter.second);
        }
        m_bitmap_cache.clear();

        for (auto& iter : m_font_cache)
        {
            al_destroy_font(iter.second);
        }
        m_font_cache.clear();
    }

    void allegro_render_controller::shutdown()
    {
        if (mp_event_queue)
        {
            al_destroy_event_queue(mp_event_queue);
        }

        al_shutdown_primitives_addon();
        al_shutdown_ttf_addon();
        al_shutdown_font_addon();
        al_shutdown_image_addon();
    }

    ALLEGRO_BITMAP* allegro_render_controller::get_bitmap(uint32_t bitmap_id) const
    {
        const auto& iter = m_sprite_cache.find(bitmap_id);
        if (iter != m_sprite_cache.end())
        {
            return iter->second;
        }

        return nullptr;
    }

    const std::string allegro_render_controller::get_assets_path() const
    {
        return std::string(al_path_cstr(al_get_standard_path(ALLEGRO_RESOURCES_PATH), '/')) + "assets/";
    }

} /// namespace render

#else

#include "plog/Log.h"
#include "allegro_render_controller.hpp"

namespace render
{
    bool allegro_render_controller::initialise()
    {
        return true;
    }

    void allegro_render_controller::process_events()
    {

    }

    bool allegro_render_controller::create_window(const window_properties& properties)
    {
        return true;
    }

    void allegro_render_controller::set_clear_color(const utilities::color& color)
    {

    }

    void allegro_render_controller::clear()
    {

    }

    void allegro_render_controller::set_transform(const transform& transform)
    {

    }

    bool allegro_render_controller::load_bitmap(const std::string& filename,
                                       const utilities::vector2& position,
                                       const utilities::vector2& size,
                                       uint32_t& bitmap_id)
    {
        bitmap_id = m_next_sprite_id++;

        return true;
    }

    bool allegro_render_controller::load_font(
        const std::string& filename,
        uint32_t font_size,
        uint32_t flags,
        uint32_t& font_id)
    {
        font_id = m_next_font_id++;

        return true;
    }

    void allegro_render_controller::render_bitmap(
        uint32_t bitmap_id,
        const utilities::vector2& position,
        uint32_t flags)
    {

    }

    void allegro_render_controller::render_fill_rect(const utilities::rectangle& rect, const utilities::color& color)
    {

    }

    void allegro_render_controller::render_draw_line(const float x1, const float y1, const float x2,
        const float y2, const utilities::color& color)
    {

    }

    void allegro_render_controller::render_text(
        const uint32_t font_id,
        const std::string& text,
        const float x,
        const float y,
        const utilities::color& color,
        const uint32_t flags)
    {

    }

    void allegro_render_controller::flip()
    {

    }

    void allegro_render_controller::destroy_window()
    {

    }

    void allegro_render_controller::shutdown()
    {

    }
}

#endif
