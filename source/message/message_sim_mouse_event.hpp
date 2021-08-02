/// @file message_sim_mouse_event.hpp
/// @brief Message that contains a mouse event to be handled by game simulation

#ifndef MESSAGE_SIM_MOUSE_EVENT_HPP
#define MESSAGE_SIM_MOUSE_EVENT_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message generated from a mouse event to be handled by the game simulation
    class message_sim_mouse_event
        : public core::message
    {
        public:
        /// @brief The message type
        static constexpr auto TYPE { "SIM_MOUSE_EVENT" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_SIM_MOUSE_EVENT_HPP
