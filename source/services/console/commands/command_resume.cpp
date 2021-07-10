/// @file command_resume.cpp

#include "command_resume.hpp"
#include "game.hpp"
#include "message_resume.hpp"

namespace services
{
    command_resume::command_resume(core::message_bus& message_bus):
        m_message_bus{message_bus}
    {

    }

    const std::vector<std::string> command_resume::get_command_names() const
    {
        return {"resume", "r"};
    }

    void command_resume::execute(const std::vector<std::string>& args) const
    {
        auto message = messages::message_resume();
        m_message_bus.send(&message);
    }
}
