/// @file message_pause.hpp
/// @brief Message that instructs the application to exit

#ifndef MESSAGE_PAUSE_HPP
#define MESSAGE_PAUSE_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messaging
{
    /// @brief Message that causes the application to pause
    class message_pause : public message
    {
        public:
        // The message type
        static constexpr auto TYPE { "MESSAGE_PAUSE" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messaging

#endif /// MESSAGE_PAUSE_HPP
