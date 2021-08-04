/// @file game_service.cpp

#include "plog/Log.h"
#include "game_service.hpp"
#include "message_game_created.hpp"
#include "message_new_game.hpp"
#include "message_sim_mouse_event.hpp"

namespace core
{
    game_service::game_service(core::message_bus* p_message_bus)
        : service{p_message_bus}
    {
        p_message_bus->subscribe(
            this,
            {
                messages::message_new_game::TYPE,
                messages::message_sim_mouse_event::TYPE
            }
        );
    }

    game_service::~game_service()
    {

    }

    bool game_service::initialise()
    {
        return true;
    }

    void game_service::update(const utilities::gametime& gametime)
    {
        if (mp_simulation)
        {
            mp_simulation->update(gametime);
        }
    }

    void game_service::draw(core::draw_manager* p_draw_manager)
    {
        if (mp_simulation)
        {
            mp_simulation->draw();
        }
    }

    void game_service::shutdown()
    {
        destroy_simulation();
    }

    void game_service::on_publish(core::message* p_message)
    {
        if (p_message->get_type() == messages::message_new_game::TYPE)
        {
            if (mp_simulation)
            {
                destroy_simulation();
            }

            create_simulation();
        }
        else if (p_message->get_type() == messages::message_sim_mouse_event::TYPE)
        {
            if (mp_simulation)
            {
                const auto p_sim_message = dynamic_cast<messages::message_sim_mouse_event*>(p_message);
                mp_simulation->on_mouse_down(p_sim_message->get_x(), p_sim_message->get_y());
            }
        }
    }

    void game_service::create_simulation()
    {
        mp_simulation = std::make_unique<simulation>(mp_message_bus);
        mp_simulation->initialise();

        auto camera = mp_simulation->get_camera("main");
        auto message = std::make_unique<messages::message_game_created>(camera);
        mp_message_bus->send(message.get());
    }

    void game_service::destroy_simulation()
    {
        if (mp_simulation)
        {
            mp_simulation->shutdown();
            mp_simulation = nullptr;
        }
    }
}
