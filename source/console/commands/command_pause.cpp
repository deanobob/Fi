/// @file command_pause.cpp

#include "command_pause.hpp"
#include "game.hpp"
#include "message_pause.hpp"

namespace console
{
    command_pause::command_pause(core::message_bus* p_message_bus):
        mp_message_bus{p_message_bus}
    {

    }

    const std::vector<std::string> command_pause::get_command_names() const
    {
        return {"pause", "p"};
    }

    void command_pause::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_pause();
        mp_message_bus->send(&message);
    }
}
