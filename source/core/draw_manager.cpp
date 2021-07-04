/// @file draw_manager.cpp

#include "plog/Log.h"
#include "draw_manager.hpp"
#include "game.hpp"
#include "time.hpp"

namespace core
{
    draw_manager::draw_manager(game* p_game)
        : mp_game{p_game}
    {
        mp_renderer = p_game->get_system_interface()->get_renderer();
        assert(mp_renderer != nullptr);

        mp_renderer->add_event_listener(this);
    }

    draw_manager::~draw_manager()
    {
        mp_renderer->remove_event_listener(this);
    }

    bool draw_manager::initialise()
    {
        framework::window_properties window_properties{};

        return mp_renderer->initialise()
            && mp_renderer->create_window(window_properties);
    }

    void draw_manager::update(const utilities::gametime& gametime)
    {
        mp_renderer->process_events();
    }

    void draw_manager::draw(double delta)
    {
        mp_renderer->clear();

        // draw stuff here
        utilities::time::sleep_msec(16);

        mp_renderer->flip();
    }

    void draw_manager::shutdown()
    {
        mp_renderer->destroy_window();
        mp_renderer->shutdown();
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
