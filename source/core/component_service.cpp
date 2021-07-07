/// @file component_service.cpp

#include "plog/Log.h"
#include "component_service.hpp"
#include "game.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"
#include "service_type.hpp"

namespace core
{
    component_service::component_service(game* p_game, component_type component_mask)
        : service(p_game)
        , m_component_mask{component_mask}
        , mp_entity_manager{mp_game->get_service<services::entity_manager>(service_type::entity_manager)}
    {
        mp_entity_manager->m_entity_status_publisher.subscribe(
            this,
            { messages::message_entity_added::TYPE,
              messages::message_entity_removed::TYPE });
    }

    component_service::~component_service()
    {
        mp_entity_manager->m_entity_status_publisher.unsubscribe(this);
    }

    void component_service::on_publish(messaging::message* p_message)
    {
        if (p_message->get_type() == messages::message_entity_added::TYPE)
        {
            messages::message_entity_added* p_added_message = dynamic_cast<messages::message_entity_added*>(p_message);
            auto p_entity = p_added_message->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.push_back(p_entity);
                PLOG_DEBUG << "Entity added";
            }
        }
        else if (p_message->get_type() == messages::message_entity_removed::TYPE)
        {
            messages::message_entity_removed* p_removed_message = dynamic_cast<messages::message_entity_removed*>(p_message);
            auto p_entity = p_removed_message->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.remove(p_entity);
                PLOG_DEBUG << "Entity removed";
            }
        }
    }

    const std::list<entity*>& component_service::get_entities()
    {
        return m_entities;
    }

    services::entity_manager* component_service::get_entity_manager()
    {
        return mp_entity_manager;
    }
}
