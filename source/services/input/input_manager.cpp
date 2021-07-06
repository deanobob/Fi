/// @file input_manager.cpp

#include "plog/Log.h"
#include "input_manager.hpp"
#include "game.hpp"

namespace services
{
    input_manager::input_manager(core::game* p_game)
        : service(p_game)
    {
        mp_input = p_game->get_system_interface()->get_input();
        assert(mp_input != nullptr);

        mp_input->add_event_listener(this);
    }

    input_manager::~input_manager()
    {
        mp_input->remove_event_listener(this);
    }

    bool input_manager::initialise()
    {
        return mp_input->initialise();
    }

    void input_manager::update(const utilities::gametime& gametime)
    {
        mp_input->process_events();
    }

    void input_manager::shutdown()
    {
        mp_input->shutdown();
    }

    const joypad_state* input_manager::get_joypad_state(unsigned int joypad_id) const
    {
        const auto& joypad_state_iter = m_joypad_states.find(joypad_id);
        if (joypad_state_iter != m_joypad_states.end())
        {
            joypad_state_iter->second;
        }
        return nullptr;
    }

    const keyboard_state* input_manager::get_keyboard_state() const
    {
        return &m_keyboard_state;
    }

    const mouse_state* input_manager::get_mouse_state() const
    {
        return &m_mouse_state;
    }

    void input_manager::on_key_state_changed(const key key_code, bool pressed)
    {
        PLOG_DEBUG << "key changed: " << static_cast<int>(key_code) << " " << pressed;

        m_keyboard_state.set_key_state(key_code, pressed);
    }

    void input_manager::on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position)
    {
        PLOG_DEBUG << "joystick axis changed: " << joypad_id << " " << joystick << " " << axis << " " << position;

        get_joypad_state(joypad_id)->set_axis_state(joystick, axis, position);
    }

    void input_manager::on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed)
    {
        PLOG_DEBUG << "joystick button changed: " << joypad_id << " " << button_id << " " << pressed;

        get_joypad_state(joypad_id)->set_button_state(button_id, pressed);
    }

    void input_manager::on_mouse_button_state_changed(const mouse_button mouse_button,
                                                      int x_position,
                                                      int y_position,
                                                      bool pressed)
    {
        PLOG_DEBUG << "mouse button changed: " << static_cast<int>(mouse_button) << " " << x_position << " " << y_position << " " << pressed;

        m_mouse_state.set_button_state(mouse_button, pressed);
    }

    void input_manager::on_mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        PLOG_DEBUG << "mouse axis changed: " << position_x << " " << position_y << " " << position_z;

        m_mouse_state.set_position_x(position_x);
        m_mouse_state.set_position_y(position_y);
        m_mouse_state.set_wheel_position(position_z);
    }

    joypad_state* input_manager::get_joypad_state(unsigned int joypad_id)
    {
        const auto& joypad_state_iter = m_joypad_states.find(joypad_id);
        if (joypad_state_iter != m_joypad_states.end())
        {
            return &joypad_state_iter->second;
        }

        const auto emplace_result = m_joypad_states.emplace(joypad_id, joypad_state());
        /// Emplace result contains tuple(iter(pair(joypad_id, joypad_state)));
        /// The following extracts iter, then joypad_state.
        return &emplace_result.first->second;
    }
}
