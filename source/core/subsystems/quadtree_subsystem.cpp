/// @file quadtree_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "entity_event_args.hpp"
#include "quadtree_subsystem.hpp"

namespace core
{
    quadtree_subsystem::quadtree_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        component_type component_mask)
        : component_subsystem{p_message_bus, p_entity_manager, component_mask}
        , m_quadtree{utilities::rectangle{-5000, -5000, 10000, 10000}} //TODO: determine world size
    {

    }

    quadtree_subsystem::~quadtree_subsystem()
    {

    }

    std::list<entity*> quadtree_subsystem::get_entities_in_region(const utilities::rectangle& region) const
    {
        return m_quadtree.query(region);
    }

    void quadtree_subsystem::on_entity_added(entity* p_entity)
    {
        // Register for position changed events from the entity
        p_entity->position_changed_event.register_handler(this);

        const auto p_body = p_entity->get_component<body_component>(component_type::body);
        if (p_body != nullptr)
        {
            const auto& position = p_body->get_position();
            const auto& size = p_body->get_size();
            if (!m_quadtree.insert(p_entity, {position.x, position.y, size.x, size.y}))
            {
                PLOG_ERROR << "Failed to insert entity " << p_entity->get_id() << " " << position.x << ":" << position.y << " " << size.x << ":" << size.y;
            }
        }
    }

    void quadtree_subsystem::on_entity_removed(entity* p_entity)
    {
        // Remove registration for position events
        p_entity->position_changed_event.unregister_handler(this);

        if (!m_quadtree.remove(p_entity))
        {
            PLOG_ERROR << "Failed to remove entity " << p_entity->get_id();
        }
    }

    void quadtree_subsystem::on_event_raised(const event_type& event_type, event_args* p_event_args)
    {
        if (event_type == core::entity::position_changed_event_type)
        {
            const auto entity_args = dynamic_cast<entity_event_args*>(p_event_args);
            auto p_entity = entity_args->get_entity();

            const auto p_body = p_entity->get_component<body_component>(component_type::body);
            if (p_body != nullptr)
            {
                const auto& position = p_body->get_position();
                const auto& size = p_body->get_size();
                if (!m_quadtree.remove(p_entity))
                {
                    PLOG_ERROR << "Failed to remove entity " << p_entity->get_id();
                }
                m_quadtree.insert(p_entity, {position.x, position.y, size.x, size.y});
            }
        }
    }
}
