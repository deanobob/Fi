/// @file component_service.cpp

#include "plog/Log.h"
#include "component_service.hpp"
#include "game.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"
#include "message_entities_cleared.hpp"

namespace core
{
    component_service::component_service(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        component_type component_mask)
        : mp_entity_manager{p_entity_manager}
        , mp_message_bus{p_message_bus}
        , m_component_mask{component_mask}

    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_entity_added::TYPE,
                messages::message_entity_removed::TYPE,
                messages::message_entities_cleared::TYPE
            }
        );
    }

    component_service::~component_service()
    {
        mp_message_bus->unsubscribe(this);
    }

    void component_service::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_entity_added::TYPE)
        {
            const auto p_entity = dynamic_cast<messages::message_entity_added*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.push_back(p_entity);
                PLOG_DEBUG << "Entity added";
            }
        }
        else if (p_message->get_type() == messages::message_entity_removed::TYPE)
        {
            const auto p_entity = dynamic_cast<messages::message_entity_removed*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.remove(p_entity);
                PLOG_DEBUG << "Entity removed";
            }
        }
        else if (p_message->get_type() == messages::message_entities_cleared::TYPE)
        {
            m_entities.clear();
            PLOG_DEBUG << "Entities cleared";
        }
        else
        {
            PLOG_ERROR << "Unhandled message type: " << p_message->get_type();
        }
    }

    const std::list<entity*>& component_service::get_entities()
    {
        return m_entities;
    }

    core::entity_manager* component_service::get_entity_manager()
    {
        return mp_entity_manager;
    }
}
