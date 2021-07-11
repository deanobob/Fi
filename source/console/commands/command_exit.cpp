/// @file command_exit.cpp

#include "command_exit.hpp"
#include "message_exit.hpp"

namespace console
{
    command_exit::command_exit(core::message_bus* p_message_bus):
        mp_message_bus{p_message_bus}
    {

    }

    const std::vector<std::string> command_exit::get_command_names() const
    {
        return {"exit", "e"};
    }

    void command_exit::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_exit();
        mp_message_bus->send(&message);
    }
}
