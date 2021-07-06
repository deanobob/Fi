/// @file joypad_state.cpp

#include "joypad_state.hpp"

#include <algorithm>

namespace services
{

void joypad_state::set_axis_state(unsigned int joystick_id, unsigned int axis_id, float position)
{
    auto joystick = get_joystick(joystick_id);
    auto axis = joystick.find(axis_id);
    if (axis != joystick.end())
    {
        axis->second = position;
    }
    else
    {
        joystick.emplace(axis_id, position);
    }
}

float joypad_state::get_axis_state(unsigned int joystick_id, unsigned int axis_id) const
{
    const auto& joystick_iter = m_joysticks.find(joystick_id);
    if (joystick_iter != m_joysticks.end())
    {
        const auto joystick = joystick_iter->second;
        const auto axis = joystick.find(axis_id);
        if (axis != joystick.end())
        {
            return axis->second;
        }
    }

    return 0.0f;
}

void joypad_state::set_button_state(int button, bool pressed)
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

bool joypad_state::is_button_pressed(int button) const
{
    return std::find(m_pressed_buttons.begin(), m_pressed_buttons.end(), button) != m_pressed_buttons.end();
}

std::map<unsigned int, float>& joypad_state::get_joystick(unsigned int joystick_id)
{
    const auto& joystick_iter = m_joysticks.find(joystick_id);
    if (joystick_iter != m_joysticks.end())
    {
        return joystick_iter->second;
    }

    auto emplace_result = m_joysticks.emplace(joystick_id, std::map<unsigned int, float>());
    return emplace_result.first->second;
}

} /// namespace services
