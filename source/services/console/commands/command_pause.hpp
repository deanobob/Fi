/// @file command_pause.hpp
/// @brief The command_pause base class

#ifndef COMMAND_PAUSE_HPP
#define COMMAND_PAUSE_HPP

#include <string>
#include "command.hpp"
#include "game.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Command class that pauses the game
    class command_pause
        : public command
    {
        public:
        /// @brief Constructor
        /// @param message_bus Reference to the game message bus
        command_pause(core::message_bus& message_bus);

        /// @brief The console command names that will invoke this command
        /// @return A vector containing all the command strings that can trigger this command
        const std::vector<std::string> get_command_names() const override;
        /// @brief Execute the command
        /// @param args Vector containing the command arguments
        void execute(const std::vector<std::string>& args) const override;

        private:
        /// @brief Reference to message_bus instance
        core::message_bus& m_message_bus;
    };
} /// namespace services

#endif /// COMMAND_PAUSE_HPP
