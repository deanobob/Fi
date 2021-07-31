/// @file window.cpp

#include "plog/Log.h"
#include "window.hpp"

namespace ui
{
    void window::on_initialise()
    {

    }

    void window::on_layout()
    {

    }

    void window::on_draw(core::draw_manager* p_draw_manager)
    {
        float x = get_world_x();
        float y = get_world_y();
        float w = get_width();
        float h = get_height();
        p_draw_manager->draw_filled_rectangle({x, y, w, h}, m_fill_color);
        p_draw_manager->draw_rectangle({x, y, w, h});
    }

    void window::mouse_button_pressed(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        m_last_mouse_position = {x_position, y_position};
        m_is_left_button_pressed = true;
    }

    void window::mouse_button_released(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        m_is_left_button_pressed = false;
    }

    void window::mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        if (m_is_left_button_pressed)
        {
            set_x(m_x + (static_cast<float>(position_x) - m_last_mouse_position.x));
            set_y(m_y + (static_cast<float>(position_y) - m_last_mouse_position.y));

            m_last_mouse_position = {position_x, position_y};
        }
    }
} /// namespace ui
