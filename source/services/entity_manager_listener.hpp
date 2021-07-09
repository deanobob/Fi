/// @file entity_manager_listener.hpp

#ifndef ENTITY_MANAGER_LISTENER
#define ENTITY_MANAGER_LISTENER

#include "entity.hpp"

/// @namespace framework namespace
namespace services
{
    /// @brief Interface that can be registered with an entity manager, providing a callback interface for entity events
    class entity_manager_listener
    {
        public:
        /// @brief Entity added event
        /// @param p_entity Pointer for the newly added entity
        virtual void on_entity_added(core::entity* p_entity) {};

        /// @brief Entity removed event
        /// @param p_entity Pointer for the removed entity
        virtual void on_entity_removed(core::entity* p_entity) {};

        /// @brief Entities cleared event
        virtual void on_entities_cleared() {};
    };
} /// services namespace

#endif /// ENTITY_MANAGER_LISTENER
