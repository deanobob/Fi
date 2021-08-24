/// @file button_set_cursor_tool.cpp

#include "plog/Log.h"
#include "button_set_cursor_tool.hpp"
#include "message_set_cursor_tool.hpp"

namespace ui
{
    button_set_cursor_tool::button_set_cursor_tool(core::message_bus* p_message_bus, core::cursor_tool_type tool_type)
        : mp_message_bus{p_message_bus}
        , m_cursor_tool{tool_type}
    {

    }

    void button_set_cursor_tool::on_press()
    {
        auto cursor_tool_type { core::cursor_tool_type::none };
        switch (m_cursor_tool)
        {
            case core::cursor_tool_type::track_0_deg:
                cursor_tool_type = core::cursor_tool_type::track_0_deg;
                break;
            case core::cursor_tool_type::track_90_deg:
                cursor_tool_type = core::cursor_tool_type::track_90_deg;
                break;
            case core::cursor_tool_type::track_180_deg:
                cursor_tool_type = core::cursor_tool_type::track_180_deg;
                break;
            case core::cursor_tool_type::track_270_deg:
                cursor_tool_type = core::cursor_tool_type::track_270_deg;
                break;
            default:
                break;
        }

        if (cursor_tool_type != core::cursor_tool_type::none)
        {
            auto message { messages::message_set_cursor_tool(cursor_tool_type) };
            mp_message_bus->send(&message);
        }
    }

    void button_set_cursor_tool::on_release()
    {

    }
} /// namespace ui
