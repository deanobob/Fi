/// @file render_service.cpp

#include "plog/Log.h"
#include "component_type.hpp"
#include "game.hpp"
#include "render_service.hpp"

namespace services
{
    render_service::render_service(core::message_bus& message_bus, core::entity_manager& entity_manager)
        : component_service{message_bus, entity_manager, core::component_type::render}
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

    void render_service::shutdown()
    {

    }
}
