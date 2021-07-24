/// @file simulation_view.cpp

#include "plog/Log.h"
#include "message_game_created.hpp"
#include "simulation_view.hpp"

namespace ui
{
    simulation_view::simulation_view(core::message_bus* p_message_bus, core::camera* p_camera)
        : node{p_message_bus}, mp_camera{p_camera}
    {
        assert(mp_camera != nullptr);

        mp_message_bus->subscribe(
            this,
            {}
        );
    }

    void simulation_view::on_initialise()
    {

    }

    void simulation_view::on_layout()
    {

    }

    void simulation_view::on_draw(core::draw_manager* p_draw_manager)
    {
        if (mp_camera)
        {
            for (const auto& renderable : mp_camera->get_renderables())
            {
                float x = std::get<0>(renderable);
                float y = std::get<1>(renderable);
                p_draw_manager->draw_line({x, y}, {x + 1, y + 1});
            }
        }
    }

    void simulation_view::mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        /// TODO: Raise mouse axis event adjusted based on camera position etc.
        /// and raise an event that the game service will pass to the simulation
    }

    void simulation_view::on_publish(core::message* p_message)
    {

    }
} /// namespace ui
