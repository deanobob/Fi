/// @file track_edit_window.cpp

#include "plog/Log.h"
#include "button_set_cursor_tool.hpp"
#include "cursor_tool_type.hpp"
#include "track_edit_window.hpp"

namespace ui
{
    track_edit_window::track_edit_window(core::message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
    {
        auto zero_deg_straight_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::ZERO_DEG_STRAIGHT_TRACK);
        zero_deg_straight_button->set_width(60);
        zero_deg_straight_button->set_height(60);
        add_child(std::move(zero_deg_straight_button));

        auto ninety_deg_straight_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::NINETY_DEG_STRAIGHT_TRACK);
        ninety_deg_straight_button->set_x(70);
        ninety_deg_straight_button->set_width(60);
        ninety_deg_straight_button->set_height(60);
        add_child(std::move(ninety_deg_straight_button));

        set_width(800);
        set_height(70);
        set_horizontal_alignment(ui::horizontal_alignment::right);
        set_padding_x(5);
        set_padding_y(5);
    }

    void track_edit_window::on_initialise()
    {

    }

    void track_edit_window::on_layout()
    {

    }

    void track_edit_window::on_draw(core::draw_manager* p_draw_manager)
    {
        float x = get_world_x();
        float y = get_world_y();
        float w = get_width();
        float h = get_height();
        p_draw_manager->draw_rectangle({x, y, w, h});
    }
} /// namespace ui
