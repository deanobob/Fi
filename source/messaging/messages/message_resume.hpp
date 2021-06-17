/// @file message_resume.hpp
/// @brief Message that instructs the application to resume if paused

#ifndef MESSAGE_RESUME_HPP
#define MESSAGE_RESUME_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that causes the application to resume if paused
    class message_resume : public messaging::message
    {
        public:
        /// @brief The message type
        static constexpr auto TYPE { "RESUME" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_RESUME_HPP
