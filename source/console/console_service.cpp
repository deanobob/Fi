/// @file console_service.cpp

#include <algorithm>
#include <string>
#include "plog/Log.h"
#include "command_add_entity.hpp"
#include "command_exit.hpp"
#include "command_pause.hpp"
#include "command_new_game.hpp"
#include "command_resume.hpp"
#include "console_service.hpp"
#include "strings.hpp"

namespace console
{
    console_service::console_service(core::message_bus* p_message_bus)
        : service{p_message_bus}
        , server{5050} // Defaults to port 5050
    {
        /// @todo re-enabled this later 
        /// add_command(std::make_shared<command_add_entity>(nullptr));
        add_command(std::make_shared<command_exit>(p_message_bus));
        add_command(std::make_shared<command_pause>(p_message_bus));
        add_command(std::make_shared<command_resume>(p_message_bus));
        add_command(std::make_shared<command_new_game>(p_message_bus));
    }

    bool console_service::initialise()
    {
        return start_listen_thread();
    }

    void console_service::load(core::resource_manager* p_resource_manager) 
    {
        
    }

    void console_service::update(const utilities::gametime& p_gametime)
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

    void console_service::draw(core::draw_manager* p_draw_manager, double delta)
    {
        
    }

    void console_service::shutdown()
    {
        stop_listen_thread();
    }

    bool console_service::pauseable() const
    {
        return false;
    }

    void console_service::on_receive(const std::string& message)
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

    void console_service::add_command(std::shared_ptr<command> command)
    {
        for (const auto& command_name : command->get_command_names())
        {
            m_commands[command_name] = command;
        }
    }
}
