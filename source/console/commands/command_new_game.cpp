/// @file command_new_game.cpp

#include "command_new_game.hpp"
#include "message_new_game.hpp"

namespace console
{
    command_new_game::command_new_game(core::message_bus* p_message_bus):
        mp_message_bus{p_message_bus}
    {

    }

    const std::vector<std::string> command_new_game::get_command_names() const
    {
        return {"new_game"};
    }

    void command_new_game::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_new_game();
        mp_message_bus->send(&message);
    }
}
