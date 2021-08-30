/// @file render_subsystem.cpp

#include <math.h>

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "render_component.hpp"
#include "render_subsystem.hpp"

namespace core
{
    render_subsystem::render_subsystem(core::message_bus* p_message_bus, core::entity_manager* p_entity_manager)
        : quadtree_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::render}}
    {

    }

    render_subsystem::~render_subsystem()
    {

    }

    bool render_subsystem::initialise()
    {
        return true;
    }

    void render_subsystem::update(const utilities::gametime& gametime)
    {

    }

    void render_subsystem::draw(camera* p_camera, double delta)
    {
        // Clear last frame renderables as they should have been rendered.
        p_camera->clear();

        // Get all renderable elements from wthin the camera viewport and add it to the camera renderable list
        for (auto& p_entity : get_entities_in_region(p_camera->get_viewport()))
        {
            if (!p_entity)
            {
                continue;
            }

            const auto p_render_component { p_entity->get_component<render_component>(component_type::render) };
            const auto p_body_component { p_entity->get_component<body_component>(component_type::body) };
            if (!p_render_component || !p_body_component)
            {
                continue;
            }

            const auto& position { p_body_component->get_interpolated_position(delta) };
            if (p_render_component->get_render_type() == "map")
            {
                const auto viewport = p_camera->get_viewport();
                const auto tile_size = 50.f;
                const auto start_x { viewport.x + (tile_size - std::fmod(viewport.x, tile_size)) };
                const auto start_y { viewport.y + (tile_size - std::fmod(viewport.y, tile_size)) };
                const auto end_x { start_x + viewport.width - std::fmod(start_x + viewport.width, tile_size) };
                const auto end_y { start_y + viewport.height - std::fmod(start_y + viewport.height, tile_size) };

                for (auto x = start_x; x <= end_x; x += tile_size)
                {
                    p_camera->add_renderable(
                        std::make_unique<renderable_line>(
                            position.x + x,
                            viewport.y,
                            position.x + x,
                            viewport.y + viewport.height,
                            utilities::colors::white,
                            0.5));
                }

                for (auto y = start_y; y <= end_y; y += tile_size)
                {
                    p_camera->add_renderable(
                        std::make_unique<renderable_line>(
                            viewport.x,
                            position.y + y,
                            viewport.x + viewport.width,
                            position.y + y,
                            utilities::colors::white,
                            0.5));
                }
            }
            else
            {
                const auto& size { p_body_component->get_size() };
                const auto& rotation { p_body_component->get_rotation() };
                p_camera->add_renderable(
                    std::make_unique<renderable_rectangle>(
                        position.x,
                        position.y,
                        size.x,
                        size.y,
                        rotation,
                        utilities::colors::green,
                        2));
            }
        }
    }

    void render_subsystem::shutdown()
    {

    }
}
