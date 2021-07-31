/// @file root.cpp

#include "plog/Log.h"
#include "root.hpp"

namespace ui
{
    root::root()
        : node{}
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
        if (mp_focused)
        {
            mp_focused->unfocused();
        }

        mp_focused = p_node;

        if (mp_focused)
        {
            mp_focused->focused();
        }
    }

    void root::on_key_state_changed(const input::key key_code, bool pressed)
    {
        if (mp_focused)
        {
            if (pressed)
            {
                mp_focused->key_pressed(key_code);
            }
            else
            {
                mp_focused->key_released(key_code);
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
                mp_focused->mouse_button_pressed(mouse_button, x_position, y_position);
            }
            else
            {
                mp_focused->mouse_button_released(mouse_button, x_position, y_position);
            }
        }
    }

    void root::on_mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        const auto p_focused = get_focusable_node_at(static_cast<float>(position_x), static_cast<float>(position_y));
        if (p_focused != mp_focused)
        {
            // New element is focused
            set_focus(p_focused);
        }

        if (mp_focused)
        {
            mp_focused->mouse_axis_changed(position_x, position_y, position_z);
        }
    }
} /// namespace ui
