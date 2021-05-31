/// @file command_exit.cpp

#include "command_exit.hpp"
#include "game.hpp"
#include "message_exit.hpp"

namespace services
{
    command_exit::command_exit(core::game* p_game):
        mp_game{p_game}
    {

    }

    const std::string command_exit::get_command_str() const
    {
        return "exit";
    }

    void command_exit::execute() const
    {
        const auto message = messaging::message_exit();
        mp_game->m_game_status_messager.publish(&message);
    }
}
