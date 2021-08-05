/// @file component_subsystem.hpp
/// @brief The component service base class

#ifndef COMPONENT_SUBSYSTEM_HPP
#define COMPONENT_SUBSYSTEM_HPP

#include <list>
#include "component_type.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"
#include "subsystem.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component subsystems
    class component_subsystem
        : public core::subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        /// @param component_mask Bitmask indicating the components an entity must have for it to be registered with
        /// the entity list.
        component_subsystem(core::message_bus* p_message_bus,
                            core::entity_manager* p_entity_manager,
                            component_type component_mask);
        /// @brief Default destructor
        virtual ~component_subsystem();

        void on_publish(message* p_message) override;

        protected:
        /// @brief Get the service entities
        /// @return The entity list
        const std::list<entity*>& get_entities();

        /// @brief Get entity manager
        /// @return Pointer to the entity manager
        core::entity_manager* get_entity_manager();

        /// @brief Method called when a new entity is added to the subsystem
        /// @param p_entity The entity
        virtual void on_entity_added(entity* p_entity) {};

        /// @brief Method called when an entity is removed from the subsystem
        /// @param p_entity The entity
        virtual void on_entity_removed(entity* p_entity) {};

        /// @brief Method called when all entities have been cleared
        virtual void on_entities_cleared() {};

        private:
        /// @brief Pointer to entity manager
        core::entity_manager* mp_entity_manager{nullptr};

        /// @brief The mask used to determine if an entity interesting to this service
        const component_type m_component_mask;

        /// @brief List containing all interesting entities
        std::list<entity*> m_entities{};
    };
} /// namespace core

#endif /// COMPONENT_SUBSYSTEM_HPP
