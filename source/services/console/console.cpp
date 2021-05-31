/// @file console.cpp

#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include "console.hpp"
#include "game.hpp"
#include "command_exit.hpp"

namespace services
{
    console::console(core::game* p_game):
        service(p_game)
    {
        add_command(std::make_unique<services::command_exit>(mp_game));
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
            for (const auto& p_command : m_command_buffer)
            {
                p_command->execute();
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

    void console::add_command(std::unique_ptr<services::command> command)
    {
        m_commands[command->get_command_str()] = std::move(command);
    }

    void console::read_input()
    {
        std::string line;
        while (m_running && std::getline(std::cin, line))
        {
            // convert line to lower
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);

            // match command name and generate instance
            std::lock_guard<std::mutex> lock(m_command_buffer_mutex);
            const auto& command_it = m_commands.find(line);
            if (command_it != m_commands.end())
            {
                m_command_buffer.push_back(command_it->second.get());
            }
            else if (line.length() > 0)
            {
                std::cout << "Unknown command: " << line << std::endl;
            }
        }
    }
}
