/// @file entity_manager.cpp

#include "plog/Log.h"
#include "entity_manager.hpp"

namespace core
{
    entity_manager::~entity_manager()
    {
        entity_components.clear();
    }

    entity_id entity_manager::create_entity()
    {
        const entity_id id = next_entity_id;
        next_entity_id++;
        entity_components[id] = std::map<component_type, std::unique_ptr<component> >();
        return id;
    }

    bool entity_manager::delete_entity(entity_id id)
    {
        const auto& entity_iter = entity_components.find(id);
        if (entity_iter == entity_components.end())
        {
            // Entity not found, return false
            return false;
        }

        // Delete entity
        entity_components.erase(entity_iter);
        return true;
    }

    bool entity_manager::add_component(std::unique_ptr<component> component, entity_id id)
    {
        const auto& entity_iter = entity_components.find(id);
        if (entity_iter == entity_components.end())
        {
            // Entity not found, return false
            return false;
        }

        // Add component to entity
        entity_iter->second.emplace(component->get_type(), std::move(component));
        return true;
    }

    bool entity_manager::remove_component(component_type type, entity_id id)
    {
        const auto& entity_iter = entity_components.find(id);
        if (entity_iter == entity_components.end())
        {
            // Entity not found, return false
            return false;
        }

        auto component_iter = entity_iter->second.find(type);
        if (component_iter == entity_iter->second.end())
        {
            // Component of given type doesn't exist
            return false;
        }

        entity_iter->second.erase(component_iter);
        return true;
    }

    template <typename T>
    T* entity_manager::get_component(component_type type, entity_id id)
    {
        const auto& entity_iter = entity_components.find(id);
        if (entity_iter == entity_components.end())
        {
            // Entity not found, return false
            return nullptr;
        }

        auto& component_iter = entity_iter->second.find(type);
        if (component_iter == entity_iter->second.end())
        {
            // Component of given type doesn't exist
            return nullptr;
        }

        return dynamic_cast<T*>(component_iter->second.get());
    }

    void entity_manager::on_publish(const messaging::message* p_message)
    {

    }
}
