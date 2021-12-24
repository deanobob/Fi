/// @file track_edit_window.cpp

#include "plog/Log.h"
#include "button_set_cursor_tool.hpp"
#include "cursor_tool_type.hpp"
#include "label.hpp"
#include "track_edit_window.hpp"

namespace ui
{
    track_edit_window::track_edit_window(core::message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
    {
        auto title_label = std::make_unique<label>("default_24");
        title_label->set_text("Track Editor");
        title_label->set_justification(text_alignment::centre);
        title_label->set_color(utilities::colors::white);
        title_label->set_height(40.f);
        add_child(std::move(title_label));

        auto track_0_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_0_deg);
        track_0_deg_button->set_icon("track1");
        track_0_deg_button->set_width(70);
        track_0_deg_button->set_height(70);
        track_0_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_0_deg_button));

        auto track_45_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_90_deg);
        track_45_deg_button->set_icon("track2");
        track_45_deg_button->set_x(80);
        track_45_deg_button->set_width(70);
        track_45_deg_button->set_height(70);
        track_45_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_45_deg_button));

        auto track_90_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_45_deg);
        track_90_deg_button->set_icon("track4");
        track_90_deg_button->set_x(155);
        track_90_deg_button->set_width(70);
        track_90_deg_button->set_height(70);
        track_90_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_90_deg_button));

        auto track_135_deg_button = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::track_135_deg);
        track_135_deg_button->set_icon("track3");
        track_135_deg_button->set_x(230);
        track_135_deg_button->set_width(70);
        track_135_deg_button->set_height(70);
        track_135_deg_button->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(track_135_deg_button));

        auto grass_tile = std::make_unique<button_set_cursor_tool>(
            mp_message_bus, core::cursor_tool_type::grass);
        grass_tile->set_icon("ground_1");
        grass_tile->set_x(305);
        grass_tile->set_width(70);
        grass_tile->set_height(70);
        grass_tile->set_vertical_alignment(ui::vertical_alignment::bottom);
        add_child(std::move(grass_tile));

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

    void track_edit_window::on_load(core::resource_manager* p_resource_manager)
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
        p_draw_manager->draw_filled_rectangle({x, y, w, h}, utilities::colors::black);
        p_draw_manager->draw_rectangle({x, y, w, h}, utilities::colors::white);
        p_draw_manager->draw_line({x, y + 40.f}, {x + w, y + 40.f}, utilities::colors::white);
    }
} /// namespace ui
