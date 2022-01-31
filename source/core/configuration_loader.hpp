/// @file configuration_loader.hpp
/// @brief Loads the game configuration from source files

#ifndef CONFIGURATION_LOADER_HPP
#define CONFIGURATION_LOADER_HPP

#include "configuration.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Loads configuration from source files
    class configuration_loader
    {
        public:
        /// @brief Loads the game configuration
        /// @return The game configuration
        static const utilities::configuration load();

        private:
        /// @brief Construct a new configuration loader object
        configuration_loader() = delete;

        /// @brief Destroy the configuration loader object
        ~configuration_loader() = delete;
    };
} /// namespace core

#endif /// CONFIGURATION_LOADER_HPP
