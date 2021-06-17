/// @file entity_manager.cpp

#include <algorithm>
#include "plog/Log.h"
#include "entity_manager.hpp"

namespace core
{
    entity_manager::~entity_manager()
    {
        m_entities.clear();
    }

    void entity_manager::put(std::unique_ptr<entity> entity)
    {
        const auto& tag = entity->get_tag();
        if (!tag.empty())
        {
            m_tagged_entities.emplace(entity->get_tag(), entity->get_id());
        }

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

        // Delete entity
        m_entities.erase(entity_iter);
        return true;
    }

    void entity_manager::on_publish(const messaging::message* p_message)
    {

    }
}
