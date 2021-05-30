/// @file game.cpp

#include "console.hpp"
#include "game.hpp"
#include "message_exit.hpp"
#include "time.hpp"

namespace core
{
    game::game()
    {
        m_game_status_messager.subscribe(this, {messaging::message_exit::TYPE});

        m_services.push_back(new services::console(this));
    }

    game::~game()
    {
        m_game_status_messager.unsubscribe(this, {messaging::message_exit::TYPE});

        for (auto& service : m_services)
        {
            delete service;
        }
    }

    void game::run()
    {
        if (initialise())
        {
            while (!m_exit_game)
            {
                update();
                utilities::time::sleep_sec(1);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        // Publish exit event so all subscribers can terminate cleanly
        auto exit_message = messaging::message_exit();
        m_game_status_messager.publish(&exit_message);
    }

    void game::on_publish(const messaging::message* p_message)
    {
        if (p_message->get_type() == messaging::message_exit::TYPE)
        {
            // Exit the game loop
            m_exit_game = true;
        }
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
            service->update(m_gametime);
        }
    }

    void game::shutdown()
    {
        for (auto& service : m_services)
        {
            service->shutdown();
        }
    }
}
