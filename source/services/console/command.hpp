/// @file command.hpp
/// @brief The command base class

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

/// @namespace services namespace
namespace services
{
    /// @brief Base class for console commands
    class command
    {
        public:
        /// @brief Default destructor
        virtual ~command() = default;

        /// @brief The console command names that will invoke this command
        /// @return A vector containing all the command strings that can trigger this command
        virtual const std::vector<std::string> get_command_names() const = 0;
        /// @brief Execute the command
        /// @param args The command arguments
        virtual void execute(const std::vector<std::string>& args) const = 0;
    };
} /// namespace services

#endif /// COMMAND_HPP
