/// @file physics_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "physics_component.hpp"
#include "physics_subsystem.hpp"

namespace core
{
    physics_subsystem::physics_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::physics}}
        , m_quadtree{utilities::rectangle{0, 0, 1000, 1000}} //TODO: determine world size
    {
        
    }

    physics_subsystem::~physics_subsystem()
    {

    }

    bool physics_subsystem::initialise()
    {
        return true;
    }

    void physics_subsystem::update(const utilities::gametime& gametime)
    {
        for (auto p_entity : get_entities())
        {
            auto p_body_component = p_entity->get_component<core::body_component>(component_type::body);
            auto p_physics_component = p_entity->get_component<core::physics_component>(component_type::physics);
            if (p_physics_component == nullptr || p_body_component == nullptr)
            {
                continue;
            }

            p_body_component->move(p_physics_component->get_velocity() * gametime.get_elapsed_time_in_seconds());
        }
    }

    void physics_subsystem::draw(camera* p_camera, double delta)
    {

    }

    void physics_subsystem::shutdown()
    {

    }

    void physics_subsystem::on_entity_added(entity* p_entity)
    {
        // TODO: register for events indicating an entity has moved, and update the quadtree.
        const auto& p_body = p_entity->get_component<body_component>(component_type::body);
        const auto& position = p_body->get_position();
        const auto& size = p_body->get_size();
        m_quadtree.insert(p_entity->get_id(), {position.x, position.y, size.x, size.y});
    }

    void physics_subsystem::on_entity_removed(entity* p_entity)
    {
        m_quadtree.remove(p_entity->get_id());
    }
}
