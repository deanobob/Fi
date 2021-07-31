/// @file message_window_resize.hpp
/// @brief Message that notifies the game that the window has been resized

#ifndef MESSAGE_RESUME_HPP
#define MESSAGE_RESUME_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies the game that the window has resized
    class message_window_resize
        : public core::message
    {
        public:
        /// @brief Construct a new message window resize object
        /// @param width The new window width
        /// @param height The new window height
        message_window_resize(int width, int height)
            : m_width{width}
            , m_height{height}
        {

        }

        /// @brief The message type
        static constexpr auto TYPE { "WINDOW_RESIZE" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the window width
        /// @return The window width
        int get_width() const
        {
            return m_width;
        }

        /// @brief Get the window height
        /// @return The window height
        int get_height() const
        {
            return m_height;
        }

        private:
        /// @brief The window width
        const int m_width;
        /// @brief The window height
        const int m_height;
    };
} /// namespace messages

#endif /// MESSAGE_RESUME_HPP
