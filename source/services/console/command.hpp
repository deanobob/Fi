/// @file command.hpp
/// @brief The command base class

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

/// @namespace services namespace
namespace services
{
    /// @brief Base class for console commands
    class command
    {
        public:
        /// @brief Constructor
        command() = default;

        /// @brief The console command that will invoke this command
        /// @return The command string
        virtual const std::string get_command_str() const = 0;

        /// @brief Execute the command
        virtual void execute() const = 0;
    };
} /// namespace services

#endif /// COMMAND_HPP
