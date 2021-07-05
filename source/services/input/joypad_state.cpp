/// @file joypad_state.cpp

#include "joypad_state.hpp"

#include <algorithm>

namespace services
{

void joypad_state::setAxisState(unsigned int stick, unsigned int axis, float position)
{
    std::vector<float> axis_list;

    auto it = stick_list.find(stick);
    if (it != stick_list.end())
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

    stick_list[stick] = axis_list;
}

float joypad_state::getAxisState(unsigned int stick, unsigned int axis) const
{
    auto it = stick_list.find(stick);
    if (it != stick_list.end())
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
        pressed_button_list.push_back(button);
    }
    else
    {
        pressed_button_list.remove(button);
    }
}

bool joypad_state::is_button_pressed(int button) const
{
    return std::find(pressed_button_list.begin(), pressed_button_list.end(), button)
        != pressed_button_list.end();
}

} /* namespace services */
