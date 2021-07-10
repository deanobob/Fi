/// @file component_service.cpp

#include "plog/Log.h"
#include "component_service.hpp"
#include "game.hpp"
#include "message.hpp"
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
        mp_game->m_message_bus.subscribe(
            this,
            {
                messages::message_entity_added::TYPE,
                messages::message_entity_removed::TYPE
            });
    }

    component_service::~component_service()
    {

    }

    void component_service::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_entity_added::TYPE)
        {
            auto p_entity = dynamic_cast<messages::message_entity_added*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.push_back(p_entity);
                PLOG_DEBUG << "Entity added";
            }
        }
        else if (p_message->get_type() == messages::message_entity_removed::TYPE)
        {
            auto p_entity = dynamic_cast<messages::message_entity_removed*>(p_message)->get_entity();
            if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
            {
                m_entities.remove(p_entity);
                PLOG_DEBUG << "Entity removed";
            }
        }
        else
        {
            PLOG_ERROR << "Unhandled message type " << p_message->get_type();
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
