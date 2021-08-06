/// @file physics_subsystem.hpp
/// @brief The physics subsystem class

#ifndef PHYSICS_SUBSYSTEM_HPP
#define PHYSICS_SUBSYSTEM_HPP

#include "camera_controller.hpp"
#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"
#include "quadtree.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Physics subsystem managing movement of physics components
    class physics_subsystem
        : public core::component_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        physics_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager);
        /// @brief Default destructor
        virtual ~physics_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return true; }

        void on_entity_added(entity* p_entity) override;

        void on_entity_removed(entity* p_entity) override;

        private:
        /// @brief Quadtree object containing the locations of all entities
        utilities::quadtree m_quadtree;
    };
} /// namespace core

#endif /// PHYSICS_SUBSYSTEM_HPP
