/// @file button.cpp

#include "plog/Log.h"
#include "button.hpp"

namespace ui
{
    void button::set_icon(const std::string& icon_tag)
    {
        m_icon_tag = icon_tag;
    }

    void button::on_initialise()
    {

    }

    void button::on_load(core::resource_manager* p_resource_manager) 
    {
        LOG_DEBUG << "MAGIC";
        if (!m_icon_tag.empty())
        {
            LOG_DEBUG << "Loading " << m_icon_tag;
            m_resource_id = p_resource_manager->get_resource_id(m_icon_tag);
        }
    }

    void button::on_layout()
    {

    }

    void button::on_draw(core::draw_manager* p_draw_manager)
    {
        float x = get_world_x();
        float y = get_world_y();
        p_draw_manager->draw_bitmap(m_resource_id, {x, y});
        
        if (is_focused())
        {
            x -= 1;
            y -= 1;
            float w = get_width() + 2;
            float h = get_height() + 2;
            p_draw_manager->draw_line({x, y}, {x + w, y});         // top left to top right
            p_draw_manager->draw_line({x + w, y}, {x + w, y + h}); // top right to bottom right
            p_draw_manager->draw_line({x, y + h}, {x + w, y + h}); // bottom left to bottom right
            p_draw_manager->draw_line({x, y}, {x, y + h});         // top left to bottom left
        }
    }

    void button::mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y)
    {
        if (mouse_button == input::mouse_button::left)
        {
            on_press();
        }
    }

    void button::mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y)
    {
        if (mouse_button == input::mouse_button::left)
        {
            on_release();
        }
    }
} /// namespace ui
