/// @file command_pause.cpp

#include "command_pause.hpp"
#include "game.hpp"
#include "message_pause.hpp"

namespace services
{
    command_pause::command_pause(core::game* p_game):
        mp_game{p_game}
    {

    }

    const std::vector<std::string> command_pause::get_command_names() const
    {
        return {"pause", "p"};
    }

    void command_pause::execute(const std::vector<std::string>& args) const
    {
        const auto message = messages::message_pause();
        mp_game->m_game_status_messager.publish(&message);
    }
}
