/// @file component_service.hpp
/// @brief The component service base class

#ifndef COMPONENT_SERVICE_HPP
#define COMPONENT_SERVICE_HPP

#include <list>
#include "component_type.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"
#include "service.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component services
    class component_service
        : public core::service
        , public core::subscriber
    {
        public:
        /// @brief Constructor
        /// @brief p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        /// @param component_mask Bitmask indicating the components an entity must have for it to be registered with
        /// the entity list.
        component_service(core::message_bus* p_message_bus,
                          core::entity_manager* p_entity_manager,
                          component_type component_mask);
        /// @brief Default destructor
        virtual ~component_service();

        void on_publish(message* p_message) override;

        protected:
        /// @brief Get the service entities
        /// @return The entity list
        const std::list<entity*>& get_entities();

        /// @brief Get entity manager
        /// @return Pointer to the entity manager
        core::entity_manager* get_entity_manager();

        private:
        /// @brief The mask used to determine if an entity interesting to this service
        const component_type m_component_mask;

        /// @brief Pointer to entity manager
        core::entity_manager* mp_entity_manager{nullptr};

        /// @brief Pointer to message bus
        core::message_bus* mp_message_bus{nullptr};

        /// @brief List containing all interesting entities
        std::list<entity*> m_entities{};
    };
} /// namespace core

#endif /// COMPONENT_SERVICE_HPP
