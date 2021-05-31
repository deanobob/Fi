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
    /// @brief Base class for console commands
    class command_exit : public command
    {
        public:
        /// @brief Constructor
        /// @param p_game Pointer to instance of the game
        command_exit(core::game* p_game);

        /// @brief The console command that will invoke this command
        /// @return The command string
        const std::string get_command_str() const override;

        /// @brief Execute the command
        void execute() const override;

        private:
        /// @brief Reference to game instance
        core::game* const mp_game;
    };
} /// namespace services

#endif /// COMMAND_EXIT_HPP
