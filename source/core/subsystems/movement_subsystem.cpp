/// @file movement_subsystem.cpp

#include <math.h>
#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "entity_event_args.hpp"
#include "movement_component.hpp"
#include "movement_subsystem.hpp"

namespace core
{
    movement_subsystem::movement_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::movement}}
    {

    }

    movement_subsystem::~movement_subsystem()
    {

    }

    bool movement_subsystem::initialise()
    {
        return true;
    }

    void movement_subsystem::update(const utilities::gametime& gametime)
    {
        for (auto p_entity : get_entities())
        {
            auto p_body_component = p_entity->get_component<core::body_component>(component_type::body);
            auto p_movement_component = p_entity->get_component<core::movement_component>(component_type::movement);
            if (p_movement_component == nullptr || p_body_component == nullptr)
            {
                continue;
            }

            p_movement_component->set_velocity(
                std::min(p_movement_component->get_velocity() + 
                         (p_movement_component->get_acceleration() * 
                          static_cast<float>(gametime.get_elapsed_time_in_seconds())), 
                         p_movement_component->get_max_velocity()));
            p_body_component->travel(p_movement_component->get_velocity() * 
                                     static_cast<float>(gametime.get_elapsed_time_in_seconds()));

            const auto& route = p_movement_component->get_path();
            auto total_distance{0.0f};
            for (const auto& route_segment : route)
            {
                total_distance += static_cast<float>(route_segment->length());
            }

            auto distance_travelled = p_body_component->get_travelled();
            if (distance_travelled < 0.f || distance_travelled > total_distance)
            {
                distance_travelled = std::fmod(distance_travelled, total_distance);
                p_body_component->set_travelled(distance_travelled);
            }

            core::path_segment* p_current_path{nullptr};
            for (const auto& route_segment : route)
            {
                const auto segment_length = static_cast<float>(route_segment->length());
                if (distance_travelled > segment_length)
                {
                    distance_travelled -= segment_length;
                    continue;
                }
                p_current_path = route_segment.get();
                break;
            }

            if (p_current_path)
            {
                p_body_component->set_position(p_current_path->get_position_at(distance_travelled));
                p_body_component->set_rotation(
                    p_current_path->get_rotation_at(distance_travelled), 
                    utilities::math::unit_type::radians);
                    
                auto event_args{entity_event_args{p_entity}};
                p_entity->position_changed_event.dispatch(&event_args);
            }
        }
    }

    void movement_subsystem::draw(camera* p_camera, double delta)
    {

    }

    void movement_subsystem::shutdown()
    {

    }
}
