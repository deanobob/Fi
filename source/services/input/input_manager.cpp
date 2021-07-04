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

    void input_manager::on_key_state_changed(const key key_code, bool pressed)
    {
        PLOG_DEBUG << "key changed: " << static_cast<int>(key_code) << " " << pressed;
    }

    void input_manager::on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position)
    {
        PLOG_DEBUG << "joystick axis changed: " << joypad_id << " " << joystick << " " << axis << " " << position;
    }

    void input_manager::on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed)
    {
        PLOG_DEBUG << "joystick button changed: " << joypad_id << " " << button_id << " " << pressed;
    }

    void input_manager::on_mouse_button_state_changed(const mouse_button mouse_button,
                                                      int x_position,
                                                      int y_position,
                                                      bool pressed)
    {
        PLOG_DEBUG << "mouse button changed: " << static_cast<int>(mouse_button) << " " << x_position << " " << y_position << " " << pressed;
    }

    void input_manager::on_mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        PLOG_DEBUG << "mouse axis changed: " << position_x << " " << position_y << " " << position_z;
    }
}
