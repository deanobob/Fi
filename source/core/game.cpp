/// @file game.cpp

#include "plog/Log.h"
#include "console.hpp"
#include "entity_manager.hpp"
#include "game.hpp"
#include "input_manager.hpp"
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

        add_service(std::make_unique<services::input_manager>(this));
        add_service(std::make_unique<services::entity_manager>(this));
        add_service(std::make_unique<services::console>(this));
        add_service(std::make_unique<draw_manager>(this));

        mp_draw_manager = get_service<draw_manager>(service_type::draw_manager);
    }

    game::~game()
    {
        m_services.clear();
    }

    void game::run()
    {
        // Fixed physics step
        const double dt = 0.01;

        if (initialise())
        {
            double current_time = utilities::time::get_current_time_in_seconds();
            double accumulator = 0.0;

            while (!m_exit_game)
            {
                double new_time = utilities::time::get_current_time_in_seconds();
                double frame_time = new_time - current_time;
                // Avoid issues with clock corrections
                if (frame_time > 0.25)
                {
                    frame_time = 0.25;
                }

                current_time = new_time;

                accumulator += frame_time;

                while (accumulator >= dt)
                {
                    m_gametime.add_elapsed_time_in_seconds(dt);

                    update();
                    accumulator -= dt;
                }

                // Pass remainder of frame time to draw manager to allow interpolation of
                // entity positions between previous and current state
                mp_draw_manager->draw(accumulator / dt);
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

    void game::on_publish(messaging::message* p_message)
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

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.second;
            success &= service->initialise();
        }

        return success;
    }

    void game::update()
    {
        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.second;
            if (!m_paused || !service->pauseable())
            {
                service->update(m_gametime);
            }
        }
    }

    void game::shutdown()
    {
        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.second;
            service->shutdown();
        }
    }

    void game::add_service(std::unique_ptr<service> service)
    {
        m_services.emplace(service->get_type(), std::move(service));
    }
}
