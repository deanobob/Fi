/// @file simulation_view.cpp

#include <math.h>
#include "plog/Log.h"
#include "simulation_view.hpp"
#include "message_sim_mouse_event.hpp"

namespace ui
{
    simulation_view::simulation_view(core::message_bus* p_message_bus, core::camera* p_camera)
        : mp_message_bus{p_message_bus}
        , mp_camera{p_camera}
    {
        assert(mp_camera != nullptr);
    }

    void simulation_view::on_initialise()
    {

    }

    void simulation_view::on_layout()
    {
        mp_camera->set_dimensions({get_width(), get_height()});
    }

    void simulation_view::on_draw(core::draw_manager* p_draw_manager)
    {
        if (mp_camera)
        {
            p_draw_manager->begin({get_world_x(), get_world_y(), get_width(), get_height()});
            p_draw_manager->clear();

            for (const auto& renderable : mp_camera->get_renderables())
            {
                const auto viewport = mp_camera->get_viewport();
                const float x = std::get<0>(renderable) - viewport.x;
                const float y = std::get<1>(renderable) - viewport.y;
                const float w = std::get<2>(renderable);
                const float h = std::get<3>(renderable);
                const float r = std::get<4>(renderable);
                const int t = std::get<5>(renderable);

                const auto cx = x + w / 2.0f;
                const auto cy = y + h / 2.0f;

                const auto tl = utilities::vector2::rotate_point(cx, cy, r, x, y);
                const auto tr = utilities::vector2::rotate_point(cx, cy, r, x + w, y);
                const auto bl = utilities::vector2::rotate_point(cx, cy, r, x, y + h);
                const auto br = utilities::vector2::rotate_point(cx, cy, r, x + w, y + h);
                const auto color = t == 1 ? utilities::color{255, 255, 0} : utilities::color{255, 255, 255};
                const auto thickness = t == 1 ? 2.f : .5f;

                p_draw_manager->draw_line(tl, tr, color, thickness); // top left to top right
                p_draw_manager->draw_line(tr, br, color, thickness); // top right to bottom right
                p_draw_manager->draw_line(bl, br, color, thickness); // bottom left to bottom right
                p_draw_manager->draw_line(tl, bl, color, thickness); // top left to bottom left
            }

            p_draw_manager->end();
        }
    }

    void simulation_view::on_focus_lost()
    {
        m_is_left_button_pressed = false;
    }

    void simulation_view::mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y)
    {
        m_last_mouse_position = {position_x, position_y};
        m_is_left_button_pressed = true;

        auto message = messages::message_sim_mouse_event{
            static_cast<int>(static_cast<float>(position_x) + mp_camera->get_viewport().x - get_world_x()),
            static_cast<int>(static_cast<float>(position_y) + mp_camera->get_viewport().y - get_world_y())};
        mp_message_bus->send(&message);
    }

    void simulation_view::mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y)
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
