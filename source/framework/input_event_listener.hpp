/// @file input_event_listener.hpp

#ifndef INPUT_EVENT_LISTENER_HPP
#define INPUT_EVENT_LISTENER_HPP

#include "key.hpp"
#include "mouse.hpp"

/// @namespace framework namespace
namespace framework
{
    /// @brief Interface that can be registered with an input, providing ability to implement responses to input events
    class input_event_listener
    {
        public:
        /// @brief Keyboard key state changed
        /// @param key_code The key code
        /// @param pressed The key state
        virtual void on_key_state_changed(const services::key key_code, bool pressed) = 0;

        /// @brief Joypad axis state changed
        /// @param joypad_id The id of the joypad that raised the event
        /// @param joystick The joystick whose state has changed
        /// @param axis The axis that changed
        /// @param position The stick position
        virtual void on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position) = 0;

        /// @brief Joypad button state changed
        /// @param joypad_id The id of the joypad that raised the event
        /// @param button_id The button whose state has changed
        /// @param pressed The button state
        virtual void on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed) = 0;

        /// @brief Mouse button state changed
        /// @param mouse_button The mouse button whose state changed
        /// @param x_position The mouse x position
        /// @param y_position The mouse y position
        /// @param pressed The mouse button state
        virtual void on_mouse_button_state_changed(const services::mouse_button mouse_button,
                                                   int x_position,
                                                   int y_position,
                                                   bool pressed) = 0;

        /// @brief Mouse axis changed
        /// @param position_x The x position
        /// @param position_y The y position
        /// @param position_z The mouse wheel position
        virtual void on_mouse_axis_changed(int position_x, int position_y, int position_z) = 0;

    };
}

#endif /// INPUT_EVENT_LISTENER_HPP
