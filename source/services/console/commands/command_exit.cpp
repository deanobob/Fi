/// @file command_exit.cpp

#include "command_exit.hpp"
#include "game.hpp"
#include "message_exit.hpp"

namespace services
{
    command_exit::command_exit(core::message_bus& message_bus):
        m_message_bus{message_bus}
    {

    }

    const std::vector<std::string> command_exit::get_command_names() const
    {
        return {"exit", "e"};
    }

    void command_exit::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_exit();
        m_message_bus.send(&message);
    }
}
