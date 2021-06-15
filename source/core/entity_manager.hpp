/// @file entity_manager.hpp
/// @brief Manages entity storage, discovery, deletion. Stores components for each entity and provides functions that
/// allow services to discover entities by their component mask

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <map>
#include <memory>
#include <stdlib.h>
#include "component.hpp"
#include "component_type.hpp"
#include "publisher.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Alias for entity ID
    using entity_id = uint32_t;

    /// @brief The base entity_manager class
    class entity_manager : public messaging::subscriber
    {
        public:
        /// @brief Publisher that notifies subscribers the entity_manager is exiting
        messaging::publisher m_entity_status_publisher{};

        /// @brief Destructor
        virtual ~entity_manager();

        /// @brief Create a new entity
        /// @return The entity's entity ID
        entity_id create_entity();

        /// @brief Remove entity
        /// @param id The ID of the entity to delete
        /// @return True on success, false if the entity was not found
        bool delete_entity(entity_id id);

        /// @brief Add component to entity
        /// @param component The component to add to the entity
        /// @param id The ID of the entity we're adding the component to
        /// @return True if added, false if entity ID doesn't exist
        bool add_component(std::unique_ptr<component> component, entity_id id);

        /// @brief Remove component from entity
        /// @param component_type The component type to remove from the entity
        /// @param id The ID of the entity we're removing the component from
        /// @return True if removed, false on failure
        bool remove_component(component_type type, entity_id id);

        /// @brief Get component from entity
        /// @param type The component type
        /// @param id The ID of the entity
        /// @return The component reference cast to template type T or nullptr
        template <typename T> T* get_component(component_type type, entity_id id);

        /// @brief Handles events from publishers the entity_manager has subscribed to
        /// @param p_message The message
        void on_publish(const messaging::message* p_message) override;

        private:
        /// @brief Stores the next entity ID
        /// @details Value incremented when an entity is created always providing a unique entity ID
        entity_id next_entity_id{1};
        /// @brief Components mapped to entity IDs
        std::map<entity_id, std::map<component_type, std::unique_ptr<component> > > entity_components{};
    };
} /// namespace core

#endif /// ENTITY_MANAGER_HPP
