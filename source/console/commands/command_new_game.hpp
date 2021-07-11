/// @file command_new_game.hpp
/// @brief The command_new_game class

#ifndef COMMAND_NEW_GAME_HPP
#define COMMAND_NEW_GAME_HPP

#include <string>
#include "command.hpp"
#include "message_bus.hpp"

/// @namespace console namespace
namespace console
{
    /// @brief Command class that creates a new game simulation
    class command_new_game
        : public command
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Pointer to the game message bus
        command_new_game(core::message_bus* p_message_bus);

        /// @brief The console command names that will invoke this command
        /// @return A vector containing all the command strings that can trigger this command
        const std::vector<std::string> get_command_names() const override;
        /// @brief Execute the command
        /// @param args Vector containing the command arguments
        void execute(const std::vector<std::string>& args) const override;

        private:
        /// @brief Pointer to message_bus instance
        core::message_bus* mp_message_bus{nullptr};
    };
} /// namespace console

#endif /// COMMAND_NEW_GAME_HPP
