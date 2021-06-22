/// @file entity_manager.cpp

#include <algorithm>
#include "plog/Log.h"
#include "entity_manager.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"

namespace services
{
    entity_manager::entity_manager(core::game* p_game)
        : service(p_game)
    {

    }

    entity_manager::~entity_manager()
    {
        for (const auto& entity_iter : m_entities)
        {
            const auto message = messages::message_entity_removed(entity_iter.second.get());
            m_entity_status_publisher.publish(&message);
        }

        m_entities.clear();
    }

    void entity_manager::update(utilities::gametime& gametime)
    {
        for (const auto& entity_iter : m_entities)
        {
            entity_iter.second->update(gametime);
        }
    }

    void entity_manager::put(std::unique_ptr<core::entity> entity)
    {
        const auto& tag = entity->get_tag();
        if (!tag.empty())
        {
            m_tagged_entities.emplace(entity->get_tag(), entity->get_id());
        }

        m_entities.emplace(entity->get_id(), std::move(entity));

        // Publish addition of entity
        const auto message = messages::message_entity_added(entity.get());
        m_entity_status_publisher.publish(&message);
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
        const auto message = messages::message_entity_removed(entity_iter->second.get());
        m_entity_status_publisher.publish(&message);

        // Delete entity
        m_entities.erase(entity_iter);
        return true;
    }

    void entity_manager::on_publish(const messaging::message* p_message)
    {

    }
}
