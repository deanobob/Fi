/// @file service.cpp

#include "game.hpp"
#include "service.hpp"

namespace core
{
    service::service(game* p_game):
        mp_game(p_game)
    {

    }


    framework::system_interface* service::get_system_interface()
    {
        return mp_game->get_system_interface();
    }
}
