/// @file render_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "render_subsystem.hpp"

namespace core
{
    render_subsystem::render_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::render}}
        , m_quadtree{utilities::rectangle{0, 0, 1000, 1000}}
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
    
    void render_subsystem::draw(std::list<std::tuple<float, float> >& renderables)
    {
        for (auto& entity_id : m_quadtree.query({0, 0, 100, 100}))
        {
            auto p_entity = get_entity_manager()->get(entity_id);
            if (p_entity)
            {
                const auto& p_body = p_entity->get_component<body_component>(component_type::body);
                const auto& position = p_body->get_position();
                renderables.push_back({position.x, position.y});
            }
        }
    }

    void render_subsystem::shutdown()
    {

    }
    
    void render_subsystem::on_entity_added(entity* p_entity)
    {
        const auto& p_body = p_entity->get_component<body_component>(component_type::body);
        const auto& position = p_body->get_position();
        const auto& size = p_body->get_size();
        m_quadtree.insert(p_entity->get_id(), {position.x, position.y, size.x, size.y});
    }

    void render_subsystem::on_entity_removed(entity* p_entity)
    {
        m_quadtree.remove(p_entity->get_id());
    }
}
