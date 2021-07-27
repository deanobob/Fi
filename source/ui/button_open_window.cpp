/// @file button_open_window.cpp

#include "plog/Log.h"
#include "button_open_window.hpp"
#include "message_open_window.hpp"

namespace ui
{
    button_open_window::button_open_window(core::message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
    {

    }

    void button_open_window::on_press()
    {
        auto message = messages::message_open_window();
        mp_message_bus->send(&message);
    }

    void button_open_window::on_release()
    {

    }
} /// namespace ui
