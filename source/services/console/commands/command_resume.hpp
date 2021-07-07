/// @file command_resume.hpp
/// @brief The command_resume base class

#ifndef COMMAND_RESUME_HPP
#define COMMAND_RESUME_HPP

#include <string>
#include "command.hpp"
#include "game.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Command class that resumes the game
    class command_resume : public command
    {
        public:
        /// @brief Constructor
        /// @param p_game Pointer to instance of the game
        command_resume(core::game* p_game);

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

#endif /// COMMAND_RESUME_HPP
