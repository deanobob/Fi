/// @file message_set_cursor_tool.hpp
/// @brief Message that sets the cursor tool

#ifndef MESSAGE_SET_CURSOR_TOOL_HPP
#define MESSAGE_SET_CURSOR_TOOL_HPP

#include "cursor_tool_type.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that sets the cursor tool
    class message_set_cursor_tool
        : public core::message
    {
        public:
        /// @brief Construct a new message set cursor tool object
        /// @param cursor_tool_type The cursor tool type
        message_set_cursor_tool(core::cursor_tool_type cursor_tool_type)
            : m_cursor_tool_type{cursor_tool_type}
        {
            
        }

        /// @brief Default destructor
        virtual ~message_set_cursor_tool() = default;

        /// @brief The message type
        static constexpr auto TYPE { "SET_CURSOR_TOOL" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the cursor tool type
        /// @return The cursor tool type
        core::cursor_tool_type get_cursor_tool_type()
        {
            return m_cursor_tool_type;
        }

        private:
        /// @brief The cursor tool type
        const core::cursor_tool_type m_cursor_tool_type;
    };
} /// namespace messages

#endif /// MESSAGE_SET_CURSOR_TOOL_HPP
