/// @file joypad_state.hpp

#ifndef JOYPAD_STATE_HPP
#define JOYPAD_STATE_HPP

#include <list>
#include <map>
#include <vector>

/// @namespace services namespace
namespace services
{
    /// @brief Class that stores the current joypad state
    class joypad_state
    {
        public:
        /// @brief Set the axis state
        /// @param joystick_id The joystick id
        /// @param axis_id The axis of the stick
        /// @param position The position of the stick on the axis
        void set_axis_state(unsigned int joystick_id, unsigned int axis_id, float position);

        /// @brief Get the position of the stick axis
        /// @param joystick_id The joystick id
        /// @param axis_id The axis of the stick
        /// @return The position of the stick on the given axis
        float get_axis_state(unsigned int joystick_id, unsigned int axis_id) const;

        /// @brief Set the button pressed state
        /// @param button The button
        /// @param pressed True if pressed, false if not pressed
        void set_button_state(int button, bool pressed);

        /// @brief Check if the button is pressed
        /// @param button The button
        /// @return True if pressed, false if not pressed
        bool is_button_pressed(int button) const;

        private:
        /// @brief Map that contains the joysticks and their axis positions
        std::map<unsigned int, std::map<unsigned int, float> > m_joysticks{};
        /// @brief List of currently pressed buttons
        std::list<unsigned int> m_pressed_buttons{};

        /// @brief Get a joystick by identifier. If the joystick does not exist it is created.
        /// @param joystick_id The joystick identifier
        /// @return The joystick axes and their positions in a map
        std::map<unsigned int, float>& get_joystick(unsigned int joystick_id);
    };
} /// namespace services

#endif /// JOYPAD_STATE_HPP
