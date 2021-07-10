/// @file command_exit.hpp
/// @brief The command_exit base class

#ifndef COMMAND_EXIT_HPP
#define COMMAND_EXIT_HPP

#include <string>
#include "command.hpp"
#include "game.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Command class that instructs the game to exit
    class command_exit
        : public command
    {
        public:
        /// @brief Constructor
        /// @param message_bus Reference to the game message bus
        command_exit(core::message_bus& message_bus);

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

#endif /// COMMAND_EXIT_HPP
