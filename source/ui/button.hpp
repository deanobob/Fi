/// @file button.hpp

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "node.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic button UI element
    class button
        : public node
    {
        public:
        /// @brief Construct a new button object
        button() = default;
        /// @brief Destroy the button object
        virtual ~button() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void mouse_button_pressed(const input::mouse_button mouse_button, int x_position, int y_position) override;

        void mouse_button_released(const input::mouse_button mouse_button, int x_position, int y_position) override;

        /// @brief Called when button is pressed
        virtual void on_press() = 0;

        /// @brief Called when button is released
        virtual void on_release() = 0;
    };
} /// namespace ui

#endif /// BUTTON_HPP
