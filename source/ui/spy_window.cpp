/// @file spy_window.cpp

#include "plog/Log.h"
#include "button_open_window.hpp"
#include "spy_window.hpp"
#include "simulation_view.hpp"
#include "window.hpp"

namespace ui
{
    spy_window::spy_window(core::message_bus* p_message_bus, core::camera* p_camera)
        : mp_message_bus{p_message_bus}
    {
        set_width(400);
        set_height(200);
        set_padding_x(5);
        set_padding_y(5);

        auto sim_view = std::make_unique<simulation_view>(mp_message_bus, p_camera);
        mp_simulation_view = sim_view.get();
        add_child(std::move(sim_view));
    }

    void spy_window::on_initialise()
    {

    }

    void spy_window::on_layout()
    {

    }

    void spy_window::on_draw(core::draw_manager* p_draw_manager)
    {
        float x = get_world_x();
        float y = get_world_y();
        float w = get_width();
        float h = get_height();
        p_draw_manager->draw_rectangle({x, y, w, h});

        x = mp_simulation_view->get_world_x();
        y = mp_simulation_view->get_world_y();
        w = mp_simulation_view->get_width();
        h = mp_simulation_view->get_height();
        p_draw_manager->draw_rectangle({x, y, w, h});
    }

    void spy_window::on_publish(core::message* p_message)
    {

    }
} /// namespace ui
