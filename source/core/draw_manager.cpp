/// @file draw_manager.cpp

#include <memory>
#include "plog/Log.h"
#include "draw_manager.hpp"
#include "message_exit.hpp"
#include "time.hpp"

namespace core
{
    draw_manager::draw_manager(core::message_bus* p_message_bus, render::render_controller* p_render_controller)
        : mp_message_bus{p_message_bus}, mp_render_controller{p_render_controller}
    {
        assert(mp_message_bus != nullptr);
        assert(mp_render_controller != nullptr);

        mp_render_controller->add_event_listener(this);
    }

    draw_manager::~draw_manager()
    {
        mp_render_controller->remove_event_listener(this);
    }

    bool draw_manager::initialise()
    {
        render::window_properties window_properties{};

        return mp_render_controller->initialise()
            && mp_render_controller->create_window(window_properties);
    }

    void draw_manager::process_events()
    {
        mp_render_controller->process_events();
    }

    void draw_manager::begin(
        const utilities::rectangle& viewport,
        const utilities::vector2& scale,
        const float rotation)
    {
        auto current_scale{utilities::vector2::ONE};
        auto current_rotation{0.0f};

        if (m_transforms.size() > 0)
        {
            // Inherit properties from parent
            const auto& current_tranform{m_transforms.front()};
            current_scale = current_tranform.scale;
            current_rotation = current_tranform.rotation;
        }

        render::transform transform{};
        transform.viewport = viewport;
        transform.scale = scale * current_scale;
        transform.rotation = rotation + current_rotation;
        m_transforms.push_back(transform);

        mp_render_controller->set_transform(transform);
    }

    void draw_manager::clear()
    {
        mp_render_controller->clear();
    }

    void draw_manager::draw_line(const utilities::vector2& p1, const utilities::vector2& p2)
    {
        mp_render_controller->render_draw_line(p1.x, p1.y, p2.x, p2.y, utilities::color(255, 255, 0));
    }

    void draw_manager::draw_filled_rectangle(const utilities::rectangle& rect, const utilities::color& color)
    {
        mp_render_controller->render_fill_rect(rect, color);
    }

    void draw_manager::draw_text(const std::string text, const utilities::vector2& position)
    {
        // TODO
    }

    void draw_manager::end()
    {
        m_transforms.pop_front();

        if (m_transforms.size() > 0)
        {
            const auto& transform = m_transforms.front();
            mp_render_controller->set_transform(transform);
        }
    }

    void draw_manager::flip()
    {
        mp_render_controller->flip();
    }

    void draw_manager::shutdown()
    {
        mp_render_controller->destroy_window();
        mp_render_controller->shutdown();
    }

    void draw_manager::on_display_close()
    {
        auto message = messages::message_exit();
        mp_message_bus->send(&message);
    }

    void draw_manager::on_display_gained_focus()
    {
        PLOG_DEBUG << "Focus gained";
    }

    void draw_manager::on_display_lost_focus()
    {
        PLOG_DEBUG << "Focus lost";
    }
}
