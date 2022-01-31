/// @file keyboard_state.cpp

#include <algorithm>
#include "keyboard_state.hpp"

namespace input
{

void keyboard_state::set_key_state(key key, bool pressed)
{
    if (pressed)
    {
        m_pressed_key_list.push_back(key);
    }
    else
    {
        m_pressed_key_list.remove(key);
    }
}

bool keyboard_state::is_key_pressed(key key) const
{
    return std::find(m_pressed_key_list.begin(), m_pressed_key_list.end(), key) != m_pressed_key_list.end();
}

} /// namespace input
