/// @file component_service.cpp

#include "plog/Log.h"
#include "component_service.hpp"
#include "game.hpp"
#include "service_type.hpp"

namespace core
{
    component_service::component_service(game* p_game, component_type component_mask)
        : service(p_game)
        , m_component_mask{component_mask}
        , mp_entity_manager{mp_game->get_service<services::entity_manager>(service_type::entity_manager)}
    {
        mp_entity_manager->add_listener(this);
    }

    component_service::~component_service()
    {
        mp_entity_manager->remove_listener(this);
    }

    void component_service::on_entity_added(core::entity* p_entity)
    {
        if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
        {
            m_entities.push_back(p_entity);
            PLOG_DEBUG << "Entity added";
        }
    }

    void component_service::on_entity_removed(core::entity* p_entity)
    {
        if ((m_component_mask & p_entity->get_component_mask()) == m_component_mask)
        {
            m_entities.remove(p_entity);
            PLOG_DEBUG << "Entity removed";
        }
    }

    void component_service::on_entities_cleared()
    {
        m_entities.clear();
        PLOG_DEBUG << "Entities cleared";
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
