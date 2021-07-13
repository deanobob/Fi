/// @file component_subsystem.cpp

#include "plog/Log.h"
#include "component_subsystem.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"
#include "message_entities_cleared.hpp"

namespace core
{
    component_subsystem::component_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        component_type component_mask)
        : subsystem{p_message_bus}
        , mp_entity_manager{p_entity_manager}
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

    component_subsystem::~component_subsystem()
    {
        mp_message_bus->unsubscribe(this);
    }

    void component_subsystem::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_entity_added::TYPE)
        {
            const auto p_entity = dynamic_cast<messages::message_entity_added*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.push_back(p_entity);
                on_entity_added(p_entity);
                PLOG_DEBUG << "Entity added";
            }
        }
        else if (p_message->get_type() == messages::message_entity_removed::TYPE)
        {
            const auto p_entity = dynamic_cast<messages::message_entity_removed*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                on_entity_removed(p_entity);
                m_entities.remove(p_entity);
                PLOG_DEBUG << "Entity removed";
            }
        }
        else if (p_message->get_type() == messages::message_entities_cleared::TYPE)
        {
            on_entities_cleared();
            m_entities.clear();
            PLOG_DEBUG << "Entities cleared";
        }
        else
        {
            PLOG_ERROR << "Unhandled message type: " << p_message->get_type();
        }
    }

    const std::list<entity*>& component_subsystem::get_entities()
    {
        return m_entities;
    }

    core::entity_manager* component_subsystem::get_entity_manager()
    {
        return mp_entity_manager;
    }
}
