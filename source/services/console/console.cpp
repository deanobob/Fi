/// @file console.cpp

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include "command_exit.hpp"
#include "console.hpp"
#include "game.hpp"
#include "strings.hpp"

namespace services
{
    console::console(core::game* p_game):
        service(p_game)
    {
        add_command(std::make_shared<services::command_exit>(mp_game));
    }

    bool console::initialise()
    {
        if (m_read_thread.joinable())
        {
            // Wait for thread if running before starting new
            m_read_thread.join();
        }
        m_read_thread = std::thread(&console::read_input, this);

        return true;
    }

    void console::update(utilities::gametime& p_gametime)
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
        m_running = false;
        if (m_read_thread.joinable())
        {
            m_read_thread.join();
        }
    }

    void console::add_command(std::shared_ptr<services::command> command)
    {
        for (const auto& command_name : command->get_command_names())
        {
            m_commands[command_name] = command;
        }
    }

    void console::read_input()
    {
        std::string line;
        while (m_running && std::getline(std::cin, line))
        {
            // Convert command to tokens
            const auto& args = utilities::strings::tokenise(line);
            if (args.size() == 0)
            {
                // Ignore empty command
                continue;
            }

            // Extract first word in command - this is the command identifier
            auto command_name = args.at(0);

            // Convert command_name to lower
            std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::tolower);

            // Match command name and generate instance
            const auto& command_it = m_commands.find(command_name);
            if (command_it != m_commands.end())
            {
                std::lock_guard<std::mutex> lock(m_command_buffer_mutex);
                // Store command and arguments in command buffer
                m_command_buffer.push_back({command_it->second.get(), args});
            }
            else
            {
                std::cout << "Unknown command: " << line << std::endl;
            }
        }
    }
}
