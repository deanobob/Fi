/// @file render_service.cpp

#include "plog/Log.h"
#include "component_type.hpp"
#include "game.hpp"
#include "render_service.hpp"

namespace render
{
    render_service::render_service(core::message_bus* p_message_bus, core::entity_manager* p_entity_manager)
        : component_service{p_message_bus, p_entity_manager, core::component_type::render}
    {

    }

    render_service::~render_service()
    {

    }

    bool render_service::initialise()
    {
        return true;
    }

    void render_service::update(const utilities::gametime& gametime)
    {

    }

    void render_service::draw(core::draw_manager* p_draw_manager)
    {

    }

    void render_service::shutdown()
    {

    }
}
