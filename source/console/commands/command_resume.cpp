/// @file command_resume.cpp

#include "command_resume.hpp"
#include "game.hpp"
#include "message_resume.hpp"

namespace console
{
    command_resume::command_resume(core::message_bus* p_message_bus):
        mp_message_bus{p_message_bus}
    {

    }

    const std::vector<std::string> command_resume::get_command_names() const
    {
        return {"resume", "r"};
    }

    void command_resume::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_resume();
        mp_message_bus->send(&message);
    }
}
