/// @file game_service.cpp

#include "plog/Log.h"
#include "game_service.hpp"
#include "message_new_game.hpp"

namespace core
{
    game_service::game_service(core::message_bus* p_message_bus)
        : service{p_message_bus}
    {

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
        
    }

    void game_service::draw(core::draw_manager* p_draw_manager)
    {

    }

    void game_service::shutdown()
    {

    }
    
    void game_service::on_publish(core::message* p_message) 
    {
        if (p_message->get_type() == messages::message_new_game::TYPE)
        {

        }
    }
}
