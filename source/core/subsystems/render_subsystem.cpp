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
        // Debug centre point
        p_camera->add_renderable(
            std::make_unique<render::renderable_circle>(
                5000,
                5000,
                5,
                utilities::colors::red,
                6));

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
            const auto& size { p_body_component->get_size() };
            const auto& rotation { p_body_component->get_rotation() };
            p_camera->add_renderable(
                std::make_unique<render::renderable_rectangle>(
                    position.x,
                    position.y,
                    size.x,
                    size.y,
                    rotation,
                    utilities::colors::green,
                    2));
        }
    }

    void render_subsystem::shutdown()
    {

    }
}
