/// @file spy_window.cpp

#include "plog/Log.h"
#include "button_open_window.hpp"
#include "spy_window.hpp"
#include "simulation_view.hpp"
#include "window.hpp"

namespace ui
{
    spy_window::spy_window(core::message_bus* p_message_bus, core::camera* p_camera)
        : root{}
        , mp_message_bus{p_message_bus}
    {
        auto sim_view = std::make_unique<simulation_view>(p_camera);
        sim_view->set_padding_x(5);
        sim_view->set_padding_y(5);
        mp_simulation_view = sim_view.get();
        add_child(std::move(sim_view), true);
    }

    void spy_window::on_initialise()
    {

    }

    void spy_window::on_layout()
    {

    }

    void spy_window::on_draw(core::draw_manager* p_draw_manager)
    {

    }

    void spy_window::on_publish(core::message* p_message)
    {
        
    }
} /// namespace ui
