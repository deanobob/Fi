/// @file command_add_entity.hpp
/// @brief Command that adds a test entity to the game

#ifndef COMMAND_ADD_ENTITY_HPP
#define COMMAND_ADD_ENTITY_HPP

#include <string>
#include "command.hpp"
#include "game.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Command class that resumes the game
    class command_add_entity
        : public command
    {
        public:
        /// @brief Constructor
        /// @param p_game Pointer to instance of the game
        command_add_entity(core::game* p_game);

        /// @brief The console command names that will invoke this command
        /// @return A vector containing all the command strings that can trigger this command
        const std::vector<std::string> get_command_names() const override;
        /// @brief Execute the command
        /// @param args Vector containing the command arguments
        void execute(const std::vector<std::string>& args) const override;

        private:
        /// @brief Reference to game instance
        core::game* mp_game{nullptr};
    };
} /// namespace services

#endif /// COMMAND_ADD_ENTITY_HPP
