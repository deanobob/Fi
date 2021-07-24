/// @file window.hpp

#ifndef WINDOW_HPP
#define WINDOW_HPP

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
        window(core::message_bus* p_message_bus);
        /// @brief Destroy the window object
        virtual ~window() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void mouse_axis_changed(int position_x, int position_y, int position_z) override;
    };
} /// namespace ui

#endif /// WINDOW_HPP
