
/// @file button_set_cursor_tool.hpp

#ifndef BUTTON_SET_CURSOR_TOOL_HPP
#define BUTTON_SET_CURSOR_TOOL_HPP

#include "button.hpp"
#include "cursor_tool_type.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic button_set_cursor_tool UI element
    class button_set_cursor_tool
        : public button
    {
        public:
        /// @brief Construct a new button_set_cursor_tool object
        /// @param p_message_bus The message bus instance
        /// @param tool_type The cursor tool type
        button_set_cursor_tool(core::message_bus* p_message_bus, core::cursor_tool_type tool_type);
        /// @brief Destroy the button_set_cursor_tool object
        virtual ~button_set_cursor_tool() = default;

        protected:
        void on_press() override;

        void on_release() override;

        private:
        /// @brief The message bus
        core::message_bus* mp_message_bus{nullptr};
        /// @brief The cursor tool type
        const core::cursor_tool_type m_cursor_tool;
    };
} /// namespace ui

#endif /// BUTTON_SET_CURSOR_TOOL_HPP
