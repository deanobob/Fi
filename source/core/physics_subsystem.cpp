/// @file physics_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "entity_event_args.hpp"
#include "physics_component.hpp"
#include "physics_subsystem.hpp"

namespace core
{
    physics_subsystem::physics_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::physics}}
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

            const auto velocity = p_physics_component->get_velocity();
            if (velocity != utilities::vector2::ZERO)
            {
                p_body_component->move(velocity * gametime.get_elapsed_time_in_seconds());
                
                auto event_args{entity_event_args{p_entity}};
                p_entity->position_changed_event.dispatch(&event_args);
            }
        }
    }

    void physics_subsystem::draw(camera* p_camera, double delta)
    {

    }

    void physics_subsystem::shutdown()
    {

    }
}
