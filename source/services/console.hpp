/// @file console.hpp
/// @brief The console base class

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "service.hpp"
#include "gametime.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Base class for services
    class console : public core::service
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        console(core::game* p_game);

        /// @brief Initialises the console reader
        bool initialise();
        /// @brief Called on every tick allowing console input to be processed
        void update(utilities::gametime& gametime) override;
    };
} /// namespace services

#endif /// CONSOLE_HPP
