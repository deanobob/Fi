/// @file quadtree_subsystem.hpp
/// @brief The quadtree subsystem class

#ifndef QUADTREE_SUBSYSTEM_HPP
#define QUADTREE_SUBSYSTEM_HPP

#include "camera_controller.hpp"
#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "event_handler.hpp"
#include "message_bus.hpp"
#include "quadtree.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for subsystems that require querying of entities by position
    class quadtree_subsystem
        : public core::component_subsystem
        , public core::event_handler
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        /// @param component_mask Bitmask indicating the components an entity must have for it to be registered with
        /// the entity list.
        quadtree_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager,
            component_type component_mask);
        /// @brief Default destructor
        virtual ~quadtree_subsystem();

        /// @brief Query the quadtree for entities within a given region
        /// @param region The region to search for entities
        /// @return A list of entities resulting from querying the quadtree 
        std::list<unsigned int> get_entities_in_region(const utilities::rectangle& region) const;

        void on_entity_added(entity* p_entity) override;

        void on_entity_removed(entity* p_entity) override;
        
        void on_event_raised(const event_type& event_type, event_args* p_event_args) override;

        private:
        /// @brief Quadtree object containing the locations of all entities
        utilities::quadtree m_quadtree;
    };
} /// namespace core

#endif /// QUADTREE_SUBSYSTEM_HPP
