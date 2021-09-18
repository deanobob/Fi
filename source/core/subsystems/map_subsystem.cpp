/// @file map_subsystem.cpp

#include <math.h>
#include "plog/Log.h"
#include "component_type.hpp"
#include "map_subsystem.hpp"
#include "math.hpp"
#include "renderable.hpp"

namespace core
{
    map_subsystem::map_subsystem(core::message_bus* p_message_bus, core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {}}
        , m_world_width{10000}
        , m_world_height{10000}
    {
        for (int i = 0; i < (m_num_tiles_x * m_num_tiles_y); i++)
        {
            /// Initialise tiles to grass
            m_map[i] = 6;
        }
    }

    map_subsystem::~map_subsystem()
    {

    }

    bool map_subsystem::initialise()
    {
        return true;
    }

    void map_subsystem::update(const utilities::gametime& gametime)
    {

    }

    void map_subsystem::draw(camera* p_camera, double delta)
    {
        // Clear last frame renderables as they should have been rendered.
        p_camera->clear();

        const auto viewport { p_camera->get_viewport() };
        const auto camera_left { viewport.x };
        const auto camera_top { viewport.y };
        const auto camera_width { viewport.width + m_tile_width };
        const auto camera_height { viewport.height + m_tile_height };
        // Loop through visible tiles rendering them
        for (auto x = camera_left; x < camera_left + camera_width; x += m_tile_width)
        {
            for (auto y = camera_top; y < camera_top + camera_height; y += m_tile_height)
            {
                // Get tile at the world position x, y
                const auto [t_x, t_y] = get_tile_at(x, y);
                if (t_x < 0 || t_x >= m_num_tiles_x || t_y < 0 || t_y >= m_num_tiles_y)
                {
                    continue;
                }

                // Calculate the position of the tile within the map
                const auto pos_x = get_map_left() + (t_x * m_tile_width);
                const auto pos_y = get_map_top() + (t_y * m_tile_height);

                // Render the tile on the map
                p_camera->add_renderable(
                    std::make_unique<render::renderable_sprite>(
                        pos_x,
                        pos_y,
                        m_map[m_num_tiles_x * t_y + t_x]));
            }
        }
    }

    void map_subsystem::shutdown()
    {

    }

    std::tuple<int, int> map_subsystem::get_tile_at(float x, float y) const
    {
        x -= get_map_left();
        y -= get_map_top();
        return {floor(x / m_tile_width), floor(y / m_tile_height)};
    }

    float map_subsystem::get_map_left() const
    {
        return (m_world_width - m_map_width) / 2.f;
    }

    float map_subsystem::get_map_top() const
    {
        return (m_world_width - m_map_height) / 2.f;
    }
}
