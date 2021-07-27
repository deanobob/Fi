/// @file message_open_window.hpp
/// @brief Message that requests a window is opened

#ifndef MESSAGE_OPEN_WINDOW_HPP
#define MESSAGE_OPEN_WINDOW_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies a new game has been created
    class message_open_window
        : public core::message
    {
        public:
        /// @brief Destroy the message open window object
        virtual ~message_open_window() = default;

        /// @brief The message type
        static constexpr auto TYPE { "OPEN_WINDOW" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_OPEN_WINDOW_HPP
