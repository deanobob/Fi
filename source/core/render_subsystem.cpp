/// @file render_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
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
        for (auto& entity_id : get_entities_in_region(p_camera->get_viewport()))
        {
            auto p_entity = get_entity_manager()->get(entity_id);
            if (p_entity)
            {
                const auto& p_body = p_entity->get_component<body_component>(component_type::body);
                const auto& position = p_body->get_interpolated_position(delta);
                const auto& size = p_body->get_size();
                p_camera->add_renderable({position.x, position.y, size.x, size.y});
                
                const auto& position2 = p_body->get_interpolated_position(delta);
                p_camera->add_renderable({position2.x, position2.y - 100, size.x, size.y});
            }
        }
    }

    void render_subsystem::shutdown()
    {

    }
}
