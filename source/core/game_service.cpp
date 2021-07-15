/// @file game_service.cpp

#include "plog/Log.h"
#include "game_service.hpp"
#include "message_new_game.hpp"

namespace core
{
    game_service::game_service(core::message_bus* p_message_bus)
        : service{p_message_bus}
    {
        p_message_bus->subscribe(
            this,
            {
                messages::message_new_game::TYPE
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
        //  TODO : This is going to be replaced with game views that have a pointer to a camera, obtained via a 
        // create game view message from the simulation. The camera contains all the render data from the game
        // from within the camera viewport.
        
        // const auto& renderables = mp_simulation->get_renderables();
        // for (auto renderable : renderables)
        // {
        //     float x = std::get<0>(renderable);
        //     float y = std::get<1>(renderable);
        //     p_draw_manager->draw_line({x, y}, {x+1, y+1}); 
        // }   
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
    }

    void game_service::create_simulation()
    {
        mp_simulation = std::make_unique<simulation>();
        mp_simulation->initialise();
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
