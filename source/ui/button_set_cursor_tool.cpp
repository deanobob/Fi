/// @file button_set_cursor_tool.cpp

#include "plog/Log.h"
#include "button_set_cursor_tool.hpp"

namespace ui
{
    button_set_cursor_tool::button_set_cursor_tool(core::message_bus* p_message_bus, core::cursor_tool_type tool_type)
        : mp_message_bus{p_message_bus}
        , m_cursor_tool{tool_type}
    {

    }

    void button_set_cursor_tool::on_press()
    {
        if (m_cursor_tool == core::cursor_tool_type::ZERO_DEG_STRAIGHT_TRACK)
        {
            LOG_DEBUG << "Zero deg straight track tool";
        }
        else if (m_cursor_tool == core::cursor_tool_type::NINETY_DEG_STRAIGHT_TRACK)
        {
            LOG_DEBUG << "Ninety deg straight track tool";
        }
    }

    void button_set_cursor_tool::on_release()
    {

    }
} /// namespace ui
