/// @file game.cpp

#include "plog/Log.h"
#include "console.hpp"
#include "draw_manager.hpp"
#include "entity_manager.hpp"
#include "game.hpp"
#include "message_exit.hpp"
#include "message_pause.hpp"
#include "message_resume.hpp"
#include "time.hpp"

namespace core
{
    game::game()
    {
        m_game_status_messager.subscribe(this, {
            messages::message_exit::TYPE,
            messages::message_pause::TYPE,
            messages::message_resume::TYPE});

        add_service(std::make_unique<services::console>(this));
        add_service(std::make_unique<services::entity_manager>(this));
        add_service(std::make_unique<services::draw_manager>(this));
    }

    void game::run()
    {
        if (initialise())
        {
            while (!m_exit_game)
            {
                update();
                utilities::time::sleep_msec(10);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        // Publish exit event so all subscribers can terminate cleanly
        auto exit_message = messages::message_exit();
        m_game_status_messager.publish(&exit_message);
    }

    void game::on_publish(const messaging::message* p_message)
    {
        if (p_message->get_type() == messages::message_pause::TYPE)
        {
            // Pause the game
            m_paused = true;
            PLOGD << "Game paused";
        }
        else if (p_message->get_type() == messages::message_resume::TYPE)
        {
            // Resume the game
            m_paused = false;
            PLOGD << "Game resumed";
        }
        else if (p_message->get_type() == messages::message_exit::TYPE)
        {
            // Exit the game loop
            m_exit_game = true;
            PLOGD << "Game exiting";
        }
    }

    framework::system_interface* game::get_system_interface()
    {
        return &m_system_interface;
    }

    bool game::initialise()
    {
        bool success = true;

        for (auto& service : m_services)
        {
            success &= service->initialise();
        }

        return success;
    }

    void game::update()
    {
        m_gametime.update();

        for (auto& service : m_services)
        {
            if (!m_paused || !service->pauseable())
            {
                service->update(m_gametime);
            }
        }
    }

    void game::shutdown()
    {
        for (auto& service : m_services)
        {
            service->shutdown();
        }
    }

    void game::add_service(std::unique_ptr<service> service)
    {
        m_services.push_back(std::move(service));
    }
}
