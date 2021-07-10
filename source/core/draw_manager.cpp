/// @file draw_manager.cpp

#include <memory>
#include "plog/Log.h"
#include "draw_manager.hpp"
#include "game.hpp"
#include "time.hpp"

namespace core
{
    draw_manager::draw_manager(game* p_game)
        : mp_game{p_game}
    {
        mp_render_controller = p_game->get_system_interface()->get_render_component();
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

    void draw_manager::draw(double delta)
    {
        mp_render_controller->clear();

        // draw stuff here
        utilities::time::sleep_msec(16);

        mp_render_controller->flip();
    }

    void draw_manager::shutdown()
    {
        mp_render_controller->destroy_window();
        mp_render_controller->shutdown();
    }

    void draw_manager::on_display_close()
    {
        mp_game->exit();
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
