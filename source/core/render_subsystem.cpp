/// @file render_subsystem.cpp

#include "plog/Log.h"
#include "component_type.hpp"
#include "render_subsystem.hpp"

namespace core
{
    render_subsystem::render_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::render}}

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
        for (auto& entity : get_entities())
        {
            PLOG_DEBUG << "Updating a thing";
        }
    }
    
    void render_subsystem::draw(std::list<std::tuple<float, float> >& renderables)
    {
        int x = 0, y = 0;
        for (auto& entity : get_entities())
        {
            PLOG_DEBUG << "Drawing a thing";
            renderables.push_back({x+=10, y+=10});
        }
    }

    void render_subsystem::shutdown()
    {

    }
}
