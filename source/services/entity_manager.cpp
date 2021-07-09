/// @file entity_manager.cpp

#include <algorithm>
#include "plog/Log.h"
#include "entity_manager.hpp"

namespace services
{
    entity_manager::entity_manager(core::game* p_game)
        : service(p_game)
    {

    }

    entity_manager::~entity_manager()
    {
        // Publish removal of all entities
        for (auto listener_iter : m_listeners)
        {
            listener_iter->on_entities_cleared();
        }

        m_entities.clear();
    }

    bool entity_manager::initialise()
    {
        return true;
    }

    void entity_manager::update(const utilities::gametime& gametime)
    {
        for (const auto& entity_iter : m_entities)
        {
            entity_iter.second->update(gametime);
        }
    }

    void entity_manager::shutdown()
    {

    }

    void entity_manager::add_listener(entity_manager_listener* p_listener)
    {
        m_listeners.push_back(p_listener);
    }

    void entity_manager::remove_listener(entity_manager_listener* p_listener)
    {
        m_listeners.remove(p_listener);
    }

    void entity_manager::put(std::unique_ptr<core::entity> entity)
    {
        const auto& tag = entity->get_tag();
        if (!tag.empty())
        {
            m_tagged_entities[entity->get_tag()] = entity->get_id();
        }

        // Publish addition of entity
        for (auto listener_iter : m_listeners)
        {
            listener_iter->on_entity_added(entity.get());
        }

        m_entities.emplace(entity->get_id(), std::move(entity));
    }

    core::entity* entity_manager::get(core::entity_id id)
    {
        const auto entity_iter = m_entities.find(id);
        if (entity_iter != m_entities.end())
        {
            return entity_iter->second.get();
        }
        return nullptr;
    }

    core::entity* entity_manager::get(const std::string& tag)
    {
        const auto entity_id_iter = m_tagged_entities.find(tag);
        if (entity_id_iter == m_tagged_entities.end())
        {
            return nullptr;
        }

        const auto entity_iter = m_entities.find(entity_id_iter->second);
        if (entity_iter == m_entities.end())
        {
            return nullptr;
        }

        return entity_iter->second.get();
    }

    bool entity_manager::remove(core::entity_id id)
    {
        const auto& entity_iter = m_entities.find(id);
        if (entity_iter == m_entities.end())
        {
            // Entity not found, return false
            return false;
        }

        // Publish removal of entity
        for (auto listener_iter : m_listeners)
        {
            listener_iter->on_entity_removed(entity_iter->second.get());
        }

        // Delete entity
        m_entities.erase(entity_iter);
        return true;
    }
}
