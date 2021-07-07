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

    const std::vector<std::string> command_exit::get_command_names() const
    {
        return {"exit", "e"};
    }

    void command_exit::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_exit();
        mp_game->m_game_status_messager.publish(&message);
    }
}
