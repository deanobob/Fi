/// @file button.cpp

#include "plog/Log.h"
#include "button.hpp"

namespace ui
{
    void button::on_initialise()
    {

    }

    void button::on_layout()
    {

    }

    void button::on_draw(core::draw_manager* p_draw_manager)
    {
        if (is_focused())
        {
            float x = get_world_x();
            float y = get_world_y();
            float w = get_width();
            float h = get_height();
            p_draw_manager->draw_line({x, y}, {x + w, y});         // top left to top right
            p_draw_manager->draw_line({x + w, y}, {x + w, y + h}); // top right to bottom right
            p_draw_manager->draw_line({x, y + h}, {x + w, y + h}); // bottom left to bottom right
            p_draw_manager->draw_line({x, y}, {x, y + h});         // top left to bottom left
        }
    }

    void button::mouse_button_pressed(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        if (mouse_button == input::mouse_button::left)
        {
            on_press();
        }
    }

    void button::mouse_button_released(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        if (mouse_button == input::mouse_button::left)
        {
            on_release();
        }
    }
} /// namespace ui
