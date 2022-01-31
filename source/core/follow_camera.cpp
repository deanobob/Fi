/// @file follow_camera.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "follow_camera.hpp"

namespace core
{
    follow_camera::follow_camera(core::entity* p_entity, const utilities::vector2& position)
        : camera{position}
        , mp_entity{p_entity}
    {
        assert(p_entity != nullptr);
    }

    void follow_camera::update(const utilities::gametime& p_gametime)
    {
        const auto p_body = mp_entity->get_component<body_component>(component_type::body);
        if (p_body)
        {
            const auto& position = p_body->get_position();
            const auto& size = p_body->get_size();
            const auto& centre = position + (size / 2.0f);
            set_position(centre);
        }
    }
}
