/// @file label.cpp

#include "plog/Log.h"
#include "label.hpp"

namespace ui
{
    label::label(const std::string& font_resource_tag)
        : m_font_resource_tag(font_resource_tag)
    {

    }

    void label::set_text(const std::string& text)
    {
        m_text = text;
    }

    void label::set_justification(const text_alignment justification)
    {
        m_justification = justification;
    }

    void label::set_color(const utilities::color& color)
    {
        m_color = color;
    }

    void label::on_initialise()
    {

    }

    void label::on_load(core::resource_manager* p_resource_manager)
    {
        m_resource_id = p_resource_manager->get_font_resource_id(m_font_resource_tag);
    }

    void label::on_layout()
    {

    }

    void label::on_draw(core::draw_manager* p_draw_manager)
    {
        auto pos_x { get_world_x() };
        auto pos_y { get_world_y() };

        if (m_justification == text_alignment::centre)
        {
            // Set to the centre of the bounds as the text centre will render at X
            pos_x += get_width() / 2.f;
        }
        else if (m_justification == text_alignment::right)
        {
            // Set to the right of the bounds as the text will render up to X
            pos_x += get_width();
        }

        p_draw_manager->draw_text(m_resource_id, m_text, {pos_x, pos_y}, m_color, m_justification);
    }

} /* namespace ui */
