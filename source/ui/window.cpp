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

    }

    void window::on_mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        PLOG_DEBUG << "Window mouse move event magic";
    }
} /// namespace ui
