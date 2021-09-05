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
    {

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

        auto tile_width {64};
        auto tile_height {32};
        auto tiles_dim {5};
        auto map_width {tile_width * tiles_dim};
        auto map_height {tile_height * tiles_dim};
        auto start_pos_x {5000 - (map_width / 2.f)};
        auto start_pos_y {5000 - (map_height / 2.f)};
        for (auto x = 0; x < tiles_dim; x++)
        {
            for (auto y = 0; y < tiles_dim; y++)
            {
                const auto [pos_x, pos_y] = utilities::math::cartToIso(
                    (x * 64),
                    (y * 64));
                LOG_DEBUG << pos_x << " " << pos_y;
                LOG_DEBUG << "S " << start_pos_x << " " << start_pos_y;
                p_camera->add_renderable(std::make_unique<render::renderable_sprite>(
                    start_pos_x + pos_x,
                    start_pos_y + pos_y,
                    m_map[tiles_dim * y + x]));
            }
        }
    }

    void map_subsystem::shutdown()
    {

    }
}
