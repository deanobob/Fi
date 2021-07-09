/// @file console.cpp

#include <algorithm>
#include <string>
#include "plog/Log.h"
#include "command_add_entity.hpp"
#include "command_exit.hpp"
#include "command_pause.hpp"
#include "command_resume.hpp"
#include "console.hpp"
#include "game.hpp"
#include "strings.hpp"

namespace services
{
    console::console(core::game* p_game)
        : service(p_game)
        , server(5050) // Defaults to port 5050
    {
        add_command(std::make_shared<services::command_add_entity>(mp_game));
        add_command(std::make_shared<services::command_exit>(mp_game));
        add_command(std::make_shared<services::command_pause>(mp_game));
        add_command(std::make_shared<services::command_resume>(mp_game));
    }

    bool console::initialise()
    {
        return start_listen_thread();
    }

    void console::update(const utilities::gametime& p_gametime)
    {
        std::lock_guard<std::mutex> lock(m_command_buffer_mutex);

        if (m_command_buffer.size() > 0)
        {
            // Execute commands and clear buffer
            for (const auto& command : m_command_buffer)
            {
                const auto& p_command = std::get<0>(command);
                const auto& args = std::get<1>(command);
                p_command->execute(args);
            }
            m_command_buffer.clear();
        }
    }

    void console::shutdown()
    {
        stop_listen_thread();
    }

    bool console::pauseable() const
    {
        return false;
    }

    void console::on_receive(const std::string& message)
    {
        // Convert command to tokens
        const auto& args = utilities::strings::tokenise(message);
        if (args.size() == 0)
        {
            // Ignore empty command
            return;
        }

        // Extract first word in command - this is the command identifier
        auto command_name = args.at(0);

        // Convert command_name to lower
        std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::tolower);

        // Match command name and save command reference in buffer
        const auto& command_it = m_commands.find(command_name);
        if (command_it != m_commands.end())
        {
            std::lock_guard<std::mutex> lock(m_command_buffer_mutex);
            // Store command and arguments in command buffer
            m_command_buffer.push_back({command_it->second.get(), args});
        }
        else
        {
            PLOGD << "Unknown command: '" << command_name << "'";
        }
    }

    void console::add_command(std::shared_ptr<services::command> command)
    {
        for (const auto& command_name : command->get_command_names())
        {
            m_commands[command_name] = command;
        }
    }
}
