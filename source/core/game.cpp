/// @file game.cpp

#include "plog/Log.h"
#include "configuration_loader.hpp"
#include "console_service.hpp"
#include "entity_manager.hpp"
#include "game.hpp"
#include "game_service.hpp"
#include "input_service.hpp"
#include "message_exit.hpp"
#include "message_pause.hpp"
#include "message_resume.hpp"
#include "time.hpp"
#include "ui_service.hpp"

namespace core
{
    game::game()
        : mp_message_bus{std::make_unique<message_bus>()}
    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_exit::TYPE,
                messages::message_pause::TYPE,
                messages::message_resume::TYPE
            }
        );

        mp_draw_manager = std::make_unique<draw_manager>(
            mp_message_bus.get(),
            get_system_interface()->get_render_controller());

        add_service(std::make_unique<input::input_service>(
            mp_message_bus.get(),
            get_system_interface()->get_input_controller()));
        add_service(std::make_unique<console::console_service>(mp_message_bus.get()));
        add_service(std::make_unique<core::game_service>(mp_message_bus.get()));
        add_service(std::make_unique<ui::ui_service>(
            mp_message_bus.get(),
            get_system_interface()->get_input_controller()));
    }

    game::~game()
    {
        m_services.clear();

        mp_message_bus.reset(nullptr);
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
                mp_draw_manager->clear();
                draw(accumulator / dt);
                mp_draw_manager->flip(); //accumulator / dt);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        // Publish exit event so all subscribers can terminate cleanly
        auto exit_message = messages::message_exit();
        mp_message_bus->send(&exit_message);
    }

    void game::on_publish(core::message* p_message)
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

        const auto config = configuration_loader::load();

        render::window_properties window_properties{};
        window_properties.width = config.get_int("display_width", render::window_properties::DEFAULT_WINDOW_WIDTH);
        window_properties.height = config.get_int("display_height", render::window_properties::DEFAULT_WINDOW_HEIGHT);
        window_properties.vsync = config.get_bool("vsync", true);
        window_properties.fullscreen = config.get_bool("fullscreen", false);
        mp_draw_manager->initialise(window_properties);

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.get();
            success &= service->initialise();
        }

        return success;
    }

    void game::update()
    {
        mp_draw_manager->process_events();

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.get();
            if (!m_paused || !service->pauseable())
            {
                service->update(m_gametime);
            }
        }
    }

    void game::draw(double delta)
    {
        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.get();
            service->draw(mp_draw_manager.get(), delta);
        }
    }

    void game::shutdown()
    {
        mp_draw_manager->shutdown();

        for (auto& service_iter : m_services)
        {
            const auto& service = service_iter.get();
            service->shutdown();
        }
    }

    void game::add_service(std::unique_ptr<service> service)
    {
        m_services.push_back(std::move(service));
    }
}
