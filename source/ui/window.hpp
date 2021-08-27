/// @file window.hpp

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "color.hpp"
#include "node.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic window UI element
    /// @details Contains and manages child elements
    class window
        : public node
    {
        public:
        /// @brief Construct a new window object
        window() = default;
        /// @brief Destroy the window object
        virtual ~window() = default;

        protected:
        void on_initialise() override;

        void on_load(core::resource_manager* p_resource_manager) override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y) override;

        void mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y) override;

        void mouse_axis_changed(int position_x, int position_y, int position_z) override;

        private:
        /// @brief Flag indicating if the left mouse is pressed
        bool m_is_left_button_pressed{false};

        /// @brief Last mouse position
        utilities::vector2 m_last_mouse_position{};

        /// @brief The window fill colour
        const utilities::color m_fill_color{0, 0, 0};
    };
} /// namespace ui

#endif /// WINDOW_HPP
