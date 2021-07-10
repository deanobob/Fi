/// @file entity_manager.hpp
/// @brief Manages entity storage, discovery, deletion. Stores components for each entity and provides functions that
/// allow services to discover entities by their component mask

#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <list>
#include <map>
#include <memory>
#include <stdlib.h>
#include "entity.hpp"
#include "message_bus.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Class that manages entities and notifies listeners when entities are added / removed
    class entity_manager
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Pointer to the game message bus
        entity_manager(message_bus* p_message_bus);
        /// @brief Destructor
        virtual ~entity_manager();

        /// @brief Initialises the entity manager
        /// @return True if successfully initialised, else false|
        bool initialise();

        /// @brief Called on every tick allowing the entities to update
        /// @param gametime The gametime maintaining instance
        void update(const utilities::gametime& gametime);

        /// @brief Called when the application is shutting down. Tidy up and clear down.
        void shutdown();

        /// @brief Add an entity
        /// @param entity The entity
        void put(std::unique_ptr<entity> entity);

        /// @brief Get entity by ID
        /// @param id The entity ID
        /// @return The entity or nullptr if not found
        entity* get(entity_id id);

        /// @brief Get entity by tag
        /// @param tag The entity tag
        /// @return The entity or nullptr if not found
        entity* get(const std::string& tag);

        /// @brief Remove entity by entity_id
        /// @param id The ID of the entity to delete
        /// @return True on success, false if the entity was not found
        bool remove(entity_id id);

        private:
        /// @brief The game message bus
        message_bus* mp_message_bus;
        /// @brief Stores entity component masks
        std::map<entity_id, std::unique_ptr<entity> > m_entities{};
        /// @brief Stores entities by tag
        std::map<const std::string, unsigned int> m_tagged_entities{};
        /// @brief List of entity IDs awaiting to be deleted
        std::list<entity_id> m_deleted_entities{};
    };
} /// namespace core

#endif /// ENTITY_MANAGER_HPP
