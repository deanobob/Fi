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
        /// @param p_message_bus The game message bus
        /// @param p_input_controller The input controller
        input_service(core::message_bus* p_message_bus, input_controller* p_input_controller);
        /// @brief Destructor
        virtual ~input_service();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager, double delta) override;

        void shutdown() override;

        void on_publish(core::message* p_message) override {};

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
                                           int position_x,
                                           int position_y,
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
