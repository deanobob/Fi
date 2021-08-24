/// @file message_sim_mouse_move.hpp
/// @brief Message that contains a mouse event to be handled by game simulation

#ifndef MESSAGE_SIM_MOUSE_MOVE_HPP
#define MESSAGE_SIM_MOUSE_MOVE_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message generated from a mouse move event to be handled by the game simulation
    class message_sim_mouse_move
        : public core::message
    {
        public:
        /// @brief The message type
        static constexpr auto TYPE { "SIM_MOUSE_MOVE" };

        /// @brief Construct a new message sim mouse event object
        /// @param x The mouse x position
        /// @param y The mouse y position
        message_sim_mouse_move(const int x, const int y)
            : m_x{x}
            , m_y{y}
        {}

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the mouse x position
        /// @return The mouse x position
        int get_x() const
        {
            return m_x;
        }

        /// @brief Get the mouse y position
        /// @return The mouse y position
        int get_y() const
        {
            return m_y;
        }

        private:
        /// @brief The mouse x position
        const int m_x;
        /// @brief The mouse y position
        const int m_y;
    };
} /// namespace messages

#endif /// MESSAGE_SIM_MOUSE_MOVE_HPP
