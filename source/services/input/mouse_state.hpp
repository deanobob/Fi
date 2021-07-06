/// @file mouse_state.hpp

#ifndef MOUSE_STATE_HPP
#define MOUSE_STATE_HPP

#include <list>
#include "mouse.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Class that stores the current mouse state
    class mouse_state
    {
        public:
        /// @brief Set the button pressed state
        /// @param button The button
        /// @param pressed True if pressed, false if not pressed
        void set_button_state(const mouse_button button, bool pressed);

        /// @brief Check if the button is pressed
        /// @param button The button
        /// @return True if pressed, false if not pressed
        bool is_button_pressed(const mouse_button button) const;

        /// @brief Set the mouse position x coordinate
        /// @param x The x coordinate
        void set_position_x(int x);

        /// @brief Get the mouse x coordinate position
        /// @return The mouse x coordinate
        int get_position_x() const;

        /// @brief Set the mouse position y coordinate
        /// @param y The y coordinate
        void set_position_y(int y);

        /// @brief Get the mouse y coordinate position
        /// @return The mouse y coordinate
        int get_position_y() const;

        /// @brief Set the mouse wheel position
        /// @param position The mouse wheel position
        void set_wheel_position(int position);

        /// @brief Get the mouse wheel position
        /// @return The mouse wheel position
        int get_wheel_position() const;

        private:
        /// @brief List of buttons that are currently pressed
        std::list<mouse_button> m_pressed_buttons{};
        /// @brief The mouse cursor x coordinate
        int m_position_x{0};
        /// @brief The mouse cursor y coordinate
        int m_position_y{0};
        /// @brief The mouse wheel position
        int m_wheel_y{0};
    };
} /// services namespace

#endif /// MOUSE_STATE_HPP
