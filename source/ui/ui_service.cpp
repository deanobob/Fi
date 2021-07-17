/// @file ui_service.cpp

#include "plog/Log.h"
#include "ui_service.hpp"
#include "window.hpp"

// TODO: remove when hack removed
#include "message_new_game.hpp"

namespace ui
{
    ui_service::ui_service(core::message_bus* p_message_bus, input::input_controller* p_input_controller)
        : service{p_message_bus}
        , mp_input_controller{p_input_controller}
    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_new_game::TYPE,
            }
        );
    }

    ui_service::~ui_service()
    {

    }

    bool ui_service::initialise()
    {
        /// @todo HACK simulating the user clicking a NEW GAME button
        auto message = messages::message_new_game{};
        mp_message_bus->send(&message);

        mp_root_node = std::make_unique<ui::root>();
        auto game_window = std::make_unique<window>();
        mp_root_node->add_child(std::move(game_window), true);

        // Register root node with input event listener to allow UI to respond to input
        mp_input_controller->add_event_listener(mp_root_node.get());

        return true;
    }

    void ui_service::update(const utilities::gametime& gametime)
    {
        if (mp_root_node)
        {
            mp_root_node->layout();
        }
    }

    void ui_service::draw(core::draw_manager* p_draw_manager)
    {
        if (mp_root_node)
        {
            mp_root_node->draw(p_draw_manager);
        }
    }

    void ui_service::shutdown()
    {
        mp_root_node.reset(nullptr);
    }
}
