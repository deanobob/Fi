/// @file simulation_view.cpp

#include "plog/Log.h"
#include "message_game_created.hpp"
#include "simulation_view.hpp"

namespace ui
{
    simulation_view::simulation_view(core::camera* p_camera)
        : mp_camera{p_camera}
    {
        assert(mp_camera != nullptr);
    }

    void simulation_view::on_initialise()
    {

    }

    void simulation_view::on_layout()
    {

    }

    void simulation_view::on_draw(core::draw_manager* p_draw_manager)
    {
        if (mp_camera)
        {
            const auto viewport = mp_camera->get_viewport();
            // TODO: consider how to restrict transform region to ui node size
            p_draw_manager->begin({get_world_x(), get_world_y(), viewport.width, viewport.height});

            for (const auto& renderable : mp_camera->get_renderables())
            {
                float x = std::get<0>(renderable) - viewport.x;
                float y = std::get<1>(renderable) - viewport.y;
                float w = std::get<2>(renderable);
                float h = std::get<3>(renderable);
                p_draw_manager->draw_line({x, y}, {x + w, y});         // top left to top right
                p_draw_manager->draw_line({x + w, y}, {x + w, y + h}); // top right to bottom right
                p_draw_manager->draw_line({x, y + h}, {x + w, y + h}); // bottom left to bottom right
                p_draw_manager->draw_line({x, y}, {x, y + h});         // top left to bottom left
            }

            p_draw_manager->end();
        }
    }

    void simulation_view::on_focus_lost()
    {
        m_is_left_button_pressed = false;
    }

    void simulation_view::mouse_button_pressed(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        m_last_mouse_position = {x_position, y_position};
        m_is_left_button_pressed = true;
    }

    void simulation_view::mouse_button_released(const input::mouse_button mouse_button, int x_position, int y_position)
    {
        m_is_left_button_pressed = false;
    }

    void simulation_view::mouse_axis_changed(int position_x, int position_y, int position_z)
    {
        if (m_is_left_button_pressed)
        {
            mp_camera->move(m_last_mouse_position - utilities::vector2{position_x, position_y});
            m_last_mouse_position = {position_x, position_y};
        }
    }
} /// namespace ui
