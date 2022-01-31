/// @file game_window.cpp

#include "plog/Log.h"
#include "button_open_window.hpp"
#include "game_window.hpp"
#include "simulation_view.hpp"
#include "spy_window.hpp"
#include "track_edit_window.hpp"

namespace ui
{
    game_window::game_window(core::message_bus* p_message_bus, core::camera* p_camera)
        : root{}
        , mp_message_bus{p_message_bus}
    {
        auto sim_view = std::make_unique<simulation_view>(mp_message_bus, p_camera);
        mp_simulation_view = sim_view.get();

        auto track_edit_panel = std::make_unique<track_edit_window>(mp_message_bus);
        mp_simulation_view->add_child(std::move(track_edit_panel));

        add_child(std::move(sim_view), true);

        mp_message_bus->subscribe(
            this,
            {
                messages::message_open_window::TYPE
            }
        );
    }

    game_window::~game_window()
    {
        mp_message_bus->unsubscribe(this);
    }

    void game_window::on_initialise()
    {

    }

    void game_window::on_load(core::resource_manager* p_resource_manager)
    {
        
    }

    void game_window::on_layout()
    {

    }

    void game_window::on_draw(core::draw_manager* p_draw_manager)
    {

    }

    void game_window::on_publish(core::message* p_message)
    {
        if (p_message->get_type() == messages::message_open_window::TYPE)
        {
            auto p_open_window_message = dynamic_cast<messages::message_open_window*>(p_message);
            auto info_window = std::make_unique<spy_window>(mp_message_bus, p_open_window_message->get_camera());
            mp_simulation_view->add_child(std::move(info_window));
        }
    }
} /// namespace ui
