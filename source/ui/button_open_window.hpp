/// @file button_open_window.hpp

#ifndef BUTTON_OPEN_WINDOW_HPP
#define BUTTON_OPEN_WINDOW_HPP

#include "button.hpp"
#include "message_open_window.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic button_open_window UI element
    class button_open_window
        : public button
    {
        public:
        /// @brief Construct a new button_open_window object
        /// @param p_message_bus The message bus instance
        button_open_window(core::message_bus* p_message_bus);
        /// @brief Destroy the button_open_window object
        virtual ~button_open_window() = default;

        protected:
        void on_press() override;

        void on_release() override;

        private:
        /// @brief The message bus
        core::message_bus* mp_message_bus{nullptr};
    };
} /// namespace ui

#endif /// BUTTON_OPEN_WINDOW_HPP
