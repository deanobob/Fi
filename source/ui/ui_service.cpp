/// @file ui_service.cpp

#include "plog/Log.h"
#include "game_window.hpp"
#include "message_game_created.hpp"
#include "message_window_resized.hpp"
#include "ui_service.hpp"

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
                messages::message_game_created::TYPE,
                messages::message_window_resize::TYPE,
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

        // Initialise UI
        mp_root_node->initialise();

        return true;
    }

    void ui_service::update(const utilities::gametime& gametime)
    {
        if (mp_root_node)
        {
            mp_root_node->measure();
            mp_root_node->layout();
        }
    }

    void ui_service::draw(core::draw_manager* p_draw_manager)
    {
        p_draw_manager->begin({0, 0, m_ui_width, m_ui_height});

        if (mp_root_node)
        {
            mp_root_node->draw(p_draw_manager);
        }
        
        p_draw_manager->end();
    }

    void ui_service::shutdown()
    {
        mp_root_node.reset(nullptr);
    }

    void ui_service::on_publish(core::message* p_message)
    {
        if (p_message->get_type() == messages::message_game_created::TYPE)
        {
            auto p_game_created_message = static_cast<messages::message_game_created*>(p_message);

            // Add game window to root
            mp_root_node = std::make_unique<game_window>(mp_message_bus, p_game_created_message->get_camera());

            // TODO: configure screen width and height somewhere
            mp_root_node->set_width(m_ui_width);
            mp_root_node->set_height(m_ui_height);

            // Register root node with input event listener to allow UI to respond to input
            mp_input_controller->add_event_listener(mp_root_node.get());
        }
        else if (p_message->get_type() == messages::message_window_resize::TYPE)
        {
            auto p_window_resize_message = static_cast<messages::message_window_resize*>(p_message);
            m_ui_width = static_cast<float>(p_window_resize_message->get_width());
            m_ui_height = static_cast<float>(p_window_resize_message->get_height());

            if (mp_root_node)
            {
                mp_root_node->set_width(m_ui_width);
                mp_root_node->set_height(m_ui_height);
            }
        }
    }
}
