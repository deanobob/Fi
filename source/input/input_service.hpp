/// @file input_service.hpp
/// @brief The input_service base class

#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <map>
#include "gametime.hpp"
#include "input_controller.hpp"
#include "input_event_listener.hpp"
#include "joypad_state.hpp"
#include "keyboard_state.hpp"
#include "mouse_state.hpp"
#include "service.hpp"

/// @namespace input namespace
namespace input
{
    /// @brief Manages rendering the game
    class input_service
        : public core::service
        , public input_event_listener
    {
        public:
        /// @brief Constructor
        /// @param p_input_controller The input controller
        input_service(input_controller* p_input_controller);
        /// @brief Destructor
        virtual ~input_service();

        /// @brief Creates the game window and loads resources
        /// @return True if initialised successfully
        bool initialise() override;

        /// @brief Method that is called on every tick, allowing draw manager to process events etc.
        /// @param gametime The game time object
        void update(const utilities::gametime& gametime) override;

        /// @brief Destroy the window and tidy up
        void shutdown() override;

        /// @brief Get the state of a joypad by id
        /// @param joypad_id The joypad identifier
        /// @return The joypad state for a given joypad id. If not found an empty joypad state is returned.
        const joypad_state* get_joypad_state(unsigned int joypad_id) const;

        /// @brief Get the current keyboard state
        /// @return The keyboard state
        const keyboard_state* get_keyboard_state() const;

        /// @brief Get the current mouse state
        /// @return The mouse state
        const mouse_state* get_mouse_state() const;

        void on_key_state_changed(const key key_code, bool pressed) override;
        void on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position) override;
        void on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed) override;
        void on_mouse_button_state_changed(const mouse_button mouse_button,
                                           int x_position,
                                           int y_position,
                                           bool pressed) override;
        void on_mouse_axis_changed(int position_x, int position_y, int position_z) override;

        private:
        /// @brief Reference to input system
        input_controller* mp_input_controller{nullptr};
        /// @brief List containing all joypad states
        std::map<unsigned int, joypad_state> m_joypad_states{};
        /// @brief The current keyboard state
        keyboard_state m_keyboard_state{};
        /// @brief The current mouse state;
        mouse_state m_mouse_state{};

        /// @brief Get a joypad state by ID
        /// @param joypad_id The joypad identifier
        /// @return The joypad state. This always succeeds as it will create a joypad state if currently missing
        joypad_state* get_joypad_state(unsigned int joypad_id);
    };
} /// namespace input

#endif /// INPUT_MANAGER_HPP