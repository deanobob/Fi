/// @file root.hpp

#ifndef ROOT_HPP
#define ROOT_HPP

#include <memory>
#include "input_event_listener.hpp"
#include "node.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root UI node
    /// @details Manages node focus
    class root
        : public node
        , public input::input_event_listener
    {
        public:
        /// @brief Construct a new root object
        root();
        /// @brief Destroy the root object
        virtual ~root() = default;

        /// @brief Add child and specify if the node is focused
        /// @param p_node The child node
        /// @param focused True if focused, else false
        void add_child(std::unique_ptr<node> p_node, bool focused);

        protected:
        void on_key_state_changed(const input::key key_code, bool pressed) override;

        void on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position) override;

        void on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed) override;

        void on_mouse_button_state_changed(const input::mouse_button mouse_button,
                                           int x_position,
                                           int y_position,
                                           bool pressed) override;

        void on_mouse_axis_changed(int position_x, int position_y, int position_z) override;

        /// @brief Set the focused node
        /// @param p_node The focused node
        void set_focus(node* p_node);

        private:
        /// @brief The focused node
        node* mp_focused{nullptr};
    };
} /// namespace ui

#endif /// ROOT_HPP
