/// @file draw_manager.cpp

#include "plog/Log.h"
#include "draw_manager.hpp"

namespace services
{
    draw_manager::draw_manager(core::game* p_game)
        : service(p_game)
    {

    }

    bool draw_manager::initialise()
    {
        mp_renderer = get_system_interface()->get_renderer();
        assert(mp_renderer != nullptr);

        framework::window_properties window_properties{};

        return mp_renderer->initialise()
            && mp_renderer->create_window(window_properties);
    }

    void draw_manager::update(utilities::gametime& p_gametime)
    {
        mp_renderer->clear();

        // draw stuff here

        mp_renderer->flip();
    }

    void draw_manager::shutdown()
    {
        mp_renderer->destroy_window();
        mp_renderer->shutdown();
    }

    bool draw_manager::pauseable() const
    {
        return false;
    }
}
