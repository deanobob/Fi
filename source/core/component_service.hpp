/// @file component_service.hpp
/// @brief The component service base class

#ifndef COMPONENT_SERVICE_HPP
#define COMPONENT_SERVICE_HPP

#include <list>
#include "component_type.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "entity_manager_listener.hpp"
#include "service.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component services
    class component_service
        : public service
        , public services::entity_manager_listener
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        component_service(game* p_game, component_type component_mask);
        /// @brief Default destructor
        virtual ~component_service();

        void on_entity_added(core::entity* p_entity) override;

        void on_entity_removed(core::entity* p_entity) override;

        protected:
        /// @brief Get the service entities
        /// @return The entity list
        const std::list<entity*>& get_entities();

        /// @brief Get entity manager
        /// @return Pointer to the entity manager
        services::entity_manager* get_entity_manager();

        private:
        /// @brief The mask used to determine if an entity interesting to this service
        const component_type m_component_mask;

        /// @brief Reference to entity manager
        services::entity_manager* const mp_entity_manager;

        /// @brief List containing all interesting entities
        std::list<entity*> m_entities{};
    };
} /// namespace core

#endif /// COMPONENT_SERVICE_HPP
