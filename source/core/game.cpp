/// @file game.cpp

#include "plog/Log.h"
#include "console.hpp"
#include "game.hpp"
#include "input_manager.hpp"
#include "message_exit.hpp"
#include "message_pause.hpp"
#include "message_resume.hpp"
#include "render_service.hpp"
#include "time.hpp"

namespace core
{
    game::game()
        : m_entity_manager{m_message_bus}
        , m_draw_manager{this}
    {
        m_message_bus.subscribe(
            this,
            {
                messages::message_exit::TYPE,
                messages::message_pause::TYPE,
                messages::message_resume::TYPE
            });

        add_service(std::make_unique<services::input_manager>(get_system_interface()->get_input_controller()));
        add_service(std::make_unique<services::console>(m_message_bus, m_entity_manager));
        add_service(std::make_unique<services::render_service>(m_message_bus, m_entity_manager));
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
                m_draw_manager.draw(accumulator / dt);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        // Publish exit event so all subscribers can terminate cleanly
        auto exit_message = messages::message_exit();
        m_message_bus.send(&exit_message);
    }

    void game::on_publish(message* p_message)
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

        m_draw_manager.initialise();
        m_entity_manager.initialise();

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.second;
            success &= service->initialise();
        }

        return success;
    }

    void game::update()
    {
        m_draw_manager.process_events();
        m_entity_manager.update(m_gametime);

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
        m_draw_manager.shutdown();

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.second;
            service->shutdown();
        }

        m_entity_manager.shutdown();
    }

    void game::add_service(std::unique_ptr<service> service)
    {
        m_services.emplace(service->get_type(), std::move(service));
    }
}
