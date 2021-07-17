/// @file root.cpp

#include "plog/Log.h"
#include "root.hpp"

namespace ui
{
    root::root()
    {
        mp_focused = this;
    }

    void root::add_child(std::unique_ptr<node> p_node, bool focused)
    {
        if (focused)
        {
            set_focus(p_node.get());
        }

        node::add_child(std::move(p_node));
    }

    void root::set_focus(node* p_node)
    {
        mp_focused = p_node;
    }

    void root::on_initialise()
    {

    }

    void root::on_layout()
    {

    }

    void root::on_draw(core::draw_manager* p_draw_manager)
    {

    }

    void root::on_key_state_changed(const input::key key_code, bool pressed)
    {
        if (mp_focused)
        {
            if (pressed)
            {
                mp_focused->on_key_press(key_code);
            }
            else
            {
                mp_focused->on_key_release(key_code);
            }
        }
    }

    void root::on_joystick_axis_changed(int joypad_id, int joystick, int axis, float position)
    {

    }

    void root::on_joystick_button_state_changed(int joypad_id, int button_id, bool pressed)
    {

    }

    void root::on_mouse_button_state_changed(const input::mouse_button mouse_button,
                                             int x_position,
                                             int y_position,
                                             bool pressed)
    {
        if (mp_focused)
        {
            if (pressed)
            {
                mp_focused->on_mouse_button_press(mouse_button, x_position, y_position);
            }
            else
            {
                mp_focused->on_mouse_button_release(mouse_button, x_position, y_position);
            }
        }
    }

    void root::on_mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        mp_focused = get_node_at(position_x, position_y);
        if (mp_focused)
        {
            mp_focused->on_mouse_axis_changed(position_x, position_y, position_z);
        }
    }
} /// namespace ui
