/// @file simulation_view.cpp

#include <math.h>
#include "plog/Log.h"
#include "simulation_view.hpp"
#include "message_sim_mouse_button.hpp"
#include "message_sim_mouse_move.hpp"

namespace ui
{
    simulation_view::simulation_view(core::message_bus* p_message_bus, core::camera* p_camera)
        : mp_message_bus{p_message_bus}
        , mp_camera{p_camera}
    {
        assert(mp_camera != nullptr);
    }

    void simulation_view::on_initialise()
    {

    }

    void simulation_view::on_load(core::resource_manager* p_resource_manager)
    {

    }

    void simulation_view::on_layout()
    {
        mp_camera->set_dimensions({get_width(), get_height()});
    }

    void simulation_view::on_draw(core::draw_manager* p_draw_manager)
    {
        if (mp_camera)
        {
            p_draw_manager->begin({get_world_x(), get_world_y(), get_width(), get_height()});
            p_draw_manager->clear();

            for (const auto& p_renderable : mp_camera->get_renderables())
            {
                const auto viewport = mp_camera->get_viewport();
                switch (p_renderable->get_type())
                {
                    case core::renderable_type::rectangle:
                        {
                            const auto p_rectangle = dynamic_cast<core::renderable_rectangle*>(p_renderable.get());
                            const auto x = p_rectangle->m_x - viewport.x;
                            const auto y = p_rectangle->m_y - viewport.y;
                            const auto w = p_rectangle->m_width;
                            const auto h = p_rectangle->m_height;
                            const auto r = p_rectangle->m_rotation;
                            const auto& color = p_rectangle->m_color;
                            const auto t = p_rectangle->m_thickness;

                            const auto cx = x + w / 2.0f;
                            const auto cy = y + h / 2.0f;

                            const auto tl = utilities::vector2::rotate_point(cx, cy, r, x, y);
                            const auto tr = utilities::vector2::rotate_point(cx, cy, r, x + w, y);
                            const auto bl = utilities::vector2::rotate_point(cx, cy, r, x, y + h);
                            const auto br = utilities::vector2::rotate_point(cx, cy, r, x + w, y + h);

                            p_draw_manager->draw_line(tl, tr, color, t); // top left to top right
                            p_draw_manager->draw_line(tr, br, color, t); // top right to bottom right
                            p_draw_manager->draw_line(bl, br, color, t); // bottom left to bottom right
                            p_draw_manager->draw_line(tl, bl, color, t); // top left to bottom left
                        }
                        break;
                    case core::renderable_type::line:
                        {
                            const auto p_line = dynamic_cast<core::renderable_line*>(p_renderable.get());
                            const auto x1 = p_line->m_x1 - viewport.x;
                            const auto y1 = p_line->m_y1 - viewport.y;
                            const auto x2 = p_line->m_x2 - viewport.x;
                            const auto y2 = p_line->m_y2 - viewport.y;
                            const auto& color = p_line->m_color;
                            const auto t = p_line->m_thickness;

                            p_draw_manager->draw_line({x1, y1}, {x2, y2}, color, t);
                        }
                        break;
                    case core::renderable_type::circle:
                        {
                            const auto p_line = dynamic_cast<core::renderable_circle*>(p_renderable.get());
                            const auto cx = p_line->m_cx - viewport.x;
                            const auto cy = p_line->m_cy - viewport.y;
                            const auto radius = p_line->m_radius;
                            const auto& color = p_line->m_color;
                            const auto t = p_line->m_thickness;

                            p_draw_manager->draw_circle(cx, cy, radius, color, t);
                        }
                        break;
                    case core::renderable_type::sprite:
                        {
                            const auto p_sprite = dynamic_cast<core::renderable_sprite*>(p_renderable.get());
                            const auto res_id = p_sprite->m_sprite_res_id;
                            const auto x = p_sprite->m_x - viewport.x;
                            const auto y = p_sprite->m_y - viewport.y;

                            p_draw_manager->draw_bitmap(res_id, {x, y});
                        }
                        break;
                    case core::renderable_type::text:
                        {
                            const auto p_text = dynamic_cast<core::renderable_text*>(p_renderable.get());
                            const auto x = p_text->m_x - viewport.x;
                            const auto y = p_text->m_y - viewport.y;
                            const auto res_id = p_text->m_font_res_id;
                            const auto text = p_text->m_text;
                            const auto color = p_text->m_color;
                            const auto alignment = p_text->m_alignment;

                            p_draw_manager->draw_text(res_id, text, {x, y}, color, alignment);
                        }
                        break;
                    default:
                        PLOG_DEBUG << "Unhandled render type: " << static_cast<uint32_t>(p_renderable->get_type());
                        break;
                }

            }

            p_draw_manager->end();
        }
    }

    void simulation_view::on_focus_lost()
    {
        m_is_right_button_pressed = false;
    }

    void simulation_view::mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y)
    {
        m_last_mouse_position = {position_x, position_y};

        if (mouse_button == input::mouse_button::right)
        {
            m_is_right_button_pressed = true;
        }

        auto message = messages::message_sim_mouse_button{
            static_cast<int>(static_cast<float>(position_x) + mp_camera->get_viewport().x - get_world_x()),
            static_cast<int>(static_cast<float>(position_y) + mp_camera->get_viewport().y - get_world_y())};
        mp_message_bus->send(&message);
    }

    void simulation_view::mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y)
    {
        m_is_right_button_pressed = false;
    }

    void simulation_view::mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        if (m_is_right_button_pressed)
        {
            mp_camera->move(m_last_mouse_position - utilities::vector2{position_x, position_y});
            m_last_mouse_position = {position_x, position_y};
        }

        auto message = messages::message_sim_mouse_move{
            static_cast<int>(static_cast<float>(position_x) + mp_camera->get_viewport().x - get_world_x()),
            static_cast<int>(static_cast<float>(position_y) + mp_camera->get_viewport().y - get_world_y())};
        mp_message_bus->send(&message);
    }
} /// namespace ui
