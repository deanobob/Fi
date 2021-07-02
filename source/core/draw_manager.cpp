/// @file draw_manager.cpp

#include "plog/Log.h"
#include "draw_manager.hpp"
#include "game.hpp"
#include "time.hpp"

namespace core
{
    draw_manager::draw_manager(game* p_game)
    {
        al_init();

        mp_renderer = p_game->get_system_interface()->get_renderer();
        assert(mp_renderer != nullptr);
    }

    bool draw_manager::initialise()
    {
        framework::window_properties window_properties{};

        return mp_renderer->initialise()
            && mp_renderer->create_window(window_properties);
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
}
