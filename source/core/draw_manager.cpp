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

    void draw_manager::draw_line(const utilities::vector2& p1, const utilities::vector2& p2)
    {
        mp_render_controller->render_draw_line(p1.x, p1.y, p2.x, p2.y, utilities::color(255, 0, 0));
    }

    void draw_manager::draw_text(const std::string text, const utilities::vector2& position)
    {
        // TODO
    }

    void draw_manager::draw(double delta)
    {
        //mp_render_controller->clear();

        // draw stuff here
        utilities::time::sleep_msec(1);

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
