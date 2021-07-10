/// @file entity_manager.cpp

#include <algorithm>
#include "plog/Log.h"
#include "entity_manager.hpp"
#include "message_entities_cleared.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"

namespace core
{
    entity_manager::entity_manager(message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
    {

    }

    entity_manager::~entity_manager()
    {

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
        // Publish entities cleared message
        messages::message_entities_cleared message{};
        mp_message_bus->send(&message);

        m_entities.clear();
    }

    void entity_manager::put(std::unique_ptr<entity> entity)
    {
        const auto& tag = entity->get_tag();
        if (!tag.empty())
        {
            m_tagged_entities[entity->get_tag()] = entity->get_id();
        }

        // Publish addition of entity
        messages::message_entity_added message(entity.get());
        mp_message_bus->send(&message);

        m_entities.emplace(entity->get_id(), std::move(entity));
    }

    entity* entity_manager::get(entity_id id)
    {
        const auto entity_iter = m_entities.find(id);
        if (entity_iter != m_entities.end())
        {
            return entity_iter->second.get();
        }
        return nullptr;
    }

    entity* entity_manager::get(const std::string& tag)
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

    bool entity_manager::remove(entity_id id)
    {
        const auto& entity_iter = m_entities.find(id);
        if (entity_iter == m_entities.end())
        {
            // Entity not found, return false
            return false;
        }

        // Publish removal of entity
        messages::message_entity_removed message(entity_iter->second.get());
        mp_message_bus->send(&message);

        // Delete entity
        m_entities.erase(entity_iter);
        return true;
    }
}
