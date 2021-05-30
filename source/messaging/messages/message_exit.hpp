/// @file message_exit.hpp
/// @brief Message that instructs the application to exit

#ifndef MESSAGE_EXIT_HPP
#define MESSAGE_EXIT_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messaging
{
    /// @brief Base class for event arguments
    class message_exit : public message
    {
        public:
        // The message type
        static constexpr auto TYPE { "MESSAGE_EXIT" };

        /// @brief Default constructor
        message_exit() = default;
        /// @brief Default destructor
        virtual ~message_exit() = default;

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messaging

#endif /// MESSAGE_EXIT_HPP
