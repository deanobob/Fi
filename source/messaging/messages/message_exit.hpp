/// @file message_exit.hpp
/// @brief Message that instructs the application to exit

#ifndef MESSAGE_EXIT_HPP
#define MESSAGE_EXIT_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messaging
{
    /// @brief Message that causes the application to exit
    class message_exit : public message
    {
        public:
        /// @brief The message type
        static constexpr auto TYPE { "MESSAGE_EXIT" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messaging

#endif /// MESSAGE_EXIT_HPP
