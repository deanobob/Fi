/// @file game_window.cpp

#include "plog/Log.h"
#include "game_window.hpp"
#include "simulation_view.hpp"

namespace ui
{
    game_window::game_window(core::camera* p_camera)
        : root{}
    {
        auto sim_view = std::make_unique<simulation_view>(p_camera);
        this->add_child(std::move(sim_view), true);
    }

    void game_window::on_initialise()
    {

    }

    void game_window::on_layout()
    {

    }

    void game_window::on_draw(core::draw_manager* p_draw_manager)
    {

    }
} /// namespace ui
