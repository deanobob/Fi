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
        p_draw_manager->draw_line({x, y}, {x + w, y});         // top left to top right
        p_draw_manager->draw_line({x + w, y}, {x + w, y + h}); // top right to bottom right
        p_draw_manager->draw_line({x, y + h}, {x + w, y + h}); // bottom left to bottom right
        p_draw_manager->draw_line({x, y}, {x, y + h});         // top left to bottom left
    }

    void window::mouse_axis_changed(int position_x, int position_y, int position_z)
    {

    }
} /// namespace ui
