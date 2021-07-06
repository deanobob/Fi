/// @file joypad_state.cpp

#include "joypad_state.hpp"

#include <algorithm>

namespace services
{

void joypad_state::set_axis_state(unsigned int stick, unsigned int axis, float position)
{
    std::vector<float> axis_list;

    auto it = m_stick_list.find(stick);
    if (it != m_stick_list.end())
    {
        axis_list = it->second;
    }

    //TODO: this can probably be deleted
    if (axis_list.size() < axis + 1)
    {
        while (axis_list.size() < axis + 1)
        {
            axis_list.push_back(0.0f);
        }
    }

    axis_list[axis] = position;

    m_stick_list[stick] = axis_list;
}

float joypad_state::get_axis_state(unsigned int stick, unsigned int axis) const
{
    auto it = m_stick_list.find(stick);
    if (it != m_stick_list.end())
    {
        std::vector<float> axis_list = it->second;

        if (axis_list.size() > axis)
        {
            return axis_list.at(axis);
        }
    }

    return 0.0f;
}

void joypad_state::set_button_state(int button, bool pressed)
{
    if (pressed)
    {
        m_pressed_button_list.push_back(button);
    }
    else
    {
        m_pressed_button_list.remove(button);
    }
}

bool joypad_state::is_button_pressed(int button) const
{
    return std::find(m_pressed_button_list.begin(), m_pressed_button_list.end(), button) != m_pressed_button_list.end();
}

} /// namespace services
