/// @file mouse_state.cpp

#include <algorithm>
#include "mouse_state.hpp"

namespace services
{

void mouse_state::set_button_state(const mouse_button button, bool pressed)
{
    if (pressed)
    {
        m_pressed_buttons.push_back(button);
    }
    else
    {
        m_pressed_buttons.remove(button);
    }
}

bool mouse_state::is_button_pressed(const mouse_button button) const
{
    return std::find(m_pressed_buttons.begin(), m_pressed_buttons.end(), button) != m_pressed_buttons.end();
}

void mouse_state::set_position_x(int x)
{
    m_position_x = x;
}

int mouse_state::get_position_x() const
{
    return m_position_x;
}

void mouse_state::set_position_y(int y)
{
    m_position_y = y;
}

int mouse_state::get_position_y() const
{
    return m_position_y;
}

void mouse_state::set_wheel_position(int y)
{
    m_wheel_y = y;
}

int mouse_state::get_wheel_position() const
{
    return m_wheel_y;
}

} /// namespace services
