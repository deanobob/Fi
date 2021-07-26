/// @file button_open_window.hpp

#ifndef BUTTON_OPEN_WINDOW_HPP
#define BUTTON_OPEN_WINDOW_HPP

#include "button.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic button_open_window UI element
    class button_open_window
        : public button
    {
        public:
        /// @brief Construct a new button_open_window object
        button_open_window() = default;
        /// @brief Destroy the button_open_window object
        virtual ~button_open_window() = default;

        protected:
        void on_press() override;

        void on_release() override;
    };
} /// namespace ui

#endif /// BUTTON_OPEN_WINDOW_HPP
