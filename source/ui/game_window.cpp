/// @file game_window.cpp

#include "plog/Log.h"
#include "button_open_window.hpp"
#include "game_window.hpp"
#include "simulation_view.hpp"

namespace ui
{
    game_window::game_window(core::camera* p_camera)
        : root{}
    {
        auto sim_view = std::make_unique<simulation_view>(p_camera);

        auto test_button = std::make_unique<button_open_window>();
        test_button->set_width(200);
        test_button->set_height(30);
        test_button->set_horizontal_alignment(horizontal_alignment::centre);
        test_button->set_vertical_alignment(vertical_alignment::bottom);
        sim_view->add_child(std::move(test_button));

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
