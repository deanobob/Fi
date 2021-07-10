/// @file input_manager.hpp
/// @brief The input_manager base class

#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <map>
#include "gametime.hpp"
#include "input_event_listener.hpp"
#include "joypad_state.hpp"
#include "keyboard_state.hpp"
#include "mouse_state.hpp"
#include "renderer.hpp"
#include "service.hpp"

/// @namespace services namespace
namespace services
{
    /// Forward declarations
    class game;

    /// @brief Manages rendering the game
    class input_manager
        : public core::service
        , public framework::input_event_listener
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        input_manager(core::game* p_game);
        /// @brief Destructor
        virtual ~input_manager();

        core::service_type get_type() const override
        {
            return core::service_type::input_manager;
        }

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
        const input::joypad_state* get_joypad_state(unsigned int joypad_id) const;

        /// @brief Get the current keyboard state
        /// @return The keyboard state
        const input::keyboard_state* get_keyboard_state() const;

        /// @brief Get the current mouse state
        /// @return The mouse state
        const input::mouse_state* get_mouse_state() const;

        void on_key_state_changed(const input::key key_code, bool pressed) override;
        void on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position) override;
        void on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed) override;
        void on_mouse_button_state_changed(const input::mouse_button mouse_button,
                                           int x_position,
                                           int y_position,
                                           bool pressed) override;
        void on_mouse_axis_changed(int position_x, int position_y, int position_z) override;

        private:
        /// @brief Reference to input system
        framework::input_controller* mp_input_controller{nullptr};
        /// @brief List containing all joypad states
        std::map<unsigned int, input::joypad_state> m_joypad_states{};
        /// @brief The current keyboard state
        input::keyboard_state m_keyboard_state{};
        /// @brief The current mouse state;
        input::mouse_state m_mouse_state{};

        /// @brief Get a joypad state by ID
        /// @param joypad_id The joypad identifier
        /// @return The joypad state. This always succeeds as it will create a joypad state if currently missing
        input::joypad_state* get_joypad_state(unsigned int joypad_id);
    };
} /// namespace services

#endif /// INPUT_MANAGER_HPP
