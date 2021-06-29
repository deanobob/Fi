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
#include "publisher.hpp"
#include "service.hpp"
#include "subscriber.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief The base entity_manager class
    class entity_manager : public core::service, public messaging::subscriber
    {
        public:
        /// @brief Publisher that notifies subscribers the entity_manager is exiting
        messaging::publisher m_entity_status_publisher{};

        /// @brief Constructor
        /// @param p_game Reference to the game
        entity_manager(core::game* p_game);
        /// @brief Destructor
        virtual ~entity_manager();

        bool initialise() override { return true; }

        void update(utilities::gametime& gametime) override;

        void shutdown() override {}

        /// @brief Add an entity
        /// @param entity The entity
        void put(std::unique_ptr<core::entity> entity);

        /// @brief Get entity by ID
        /// @param id The entity ID
        /// @return The entity or nullptr if not found
        core::entity* get(core::entity_id id);

        /// @brief Get entity by tag
        /// @param tag The entity tag
        /// @return The entity or nullptr if not found
        core::entity* get(const std::string& tag);

        /// @brief Remove entity by entity_id
        /// @param id The ID of the entity to delete
        /// @return True on success, false if the entity was not found
        bool remove(core::entity_id id);

        /// @brief Handles events from publishers the entity_manager has subscribed to
        /// @param p_message The message
        void on_publish(const messaging::message* p_message) override;

        private:
        /// @brief Stores entity component masks
        std::map<core::entity_id, std::unique_ptr<core::entity> > m_entities{};
        /// @brief Stores entities by tag
        std::map<const std::string, unsigned int> m_tagged_entities{};
        /// @brief Contains a list of entity IDs awaiting to be deleted
        std::list<core::entity_id> m_deleted_entities{};
    };
} /// namespace core

#endif /// ENTITY_MANAGER_HPP
