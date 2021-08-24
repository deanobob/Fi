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
        auto track_0_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_0_deg);
        track_0_deg_button->set_width(70);
        track_0_deg_button->set_height(70);
        track_0_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_0_deg_button));

        auto track_90_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_90_deg);
        track_90_deg_button->set_x(80);
        track_90_deg_button->set_width(70);
        track_90_deg_button->set_height(70);
        track_90_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_90_deg_button));

        auto track_180_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_180_deg);
        track_180_deg_button->set_x(155);
        track_180_deg_button->set_width(70);
        track_180_deg_button->set_height(70);
        track_180_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_180_deg_button));

        auto track_270_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_270_deg);
        track_270_deg_button->set_x(230);
        track_270_deg_button->set_width(70);
        track_270_deg_button->set_height(70);
        track_270_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_270_deg_button));

        set_width(800);
        set_height(120);
        set_padding_x(5);
        set_padding_y(5);
        set_margin_x(5);
        set_margin_y(5);
        set_horizontal_alignment(ui::horizontal_alignment::right);
        set_vertical_alignment(ui::vertical_alignment::top);
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
        p_draw_manager->draw_filled_rectangle({x, y, w, h}, {0, 0, 0});
        p_draw_manager->draw_rectangle({x, y, w, h}, {255, 255, 255});
        p_draw_manager->draw_line({x, y + 40.f}, {x + w, y + 40.f}, {255, 255, 255});
    }
} /// namespace ui
