/// @file component_service.hpp
/// @brief The component service base class

#ifndef COMPONENT_SERVICE_HPP
#define COMPONENT_SERVICE_HPP

#include <list>
#include "component_type.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "service.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component services
    class component_service
        : public service
        , public subscriber
    {
        public:
        /// @brief Constructor
        /// @param message_bus Reference to the game message bus
        /// @param entity_manager Reference to the entity manager
        /// @param component_mask Bitmask indicating the components an entity must have for it to be registered with
        /// the entity list.
        component_service(message_bus& message_bus,
                          core::entity_manager& entity_manager,
                          component_type component_mask);
        /// @brief Default destructor
        virtual ~component_service();

        void on_publish(message* p_message) override;

        protected:
        /// @brief Get the service entities
        /// @return The entity list
        const std::list<entity*>& get_entities();

        /// @brief Get entity manager
        /// @return Reference to the entity manager
        core::entity_manager& get_entity_manager();

        private:
        /// @brief The game message bus
        message_bus& m_message_bus;
        /// @brief Reference to entity manager
        core::entity_manager& m_entity_manager;
        /// @brief The mask used to determine if an entity interesting to this service
        const component_type m_component_mask;
        /// @brief List containing all interesting entities
        std::list<entity*> m_entities{};
    };
} /// namespace core

#endif /// COMPONENT_SERVICE_HPP
