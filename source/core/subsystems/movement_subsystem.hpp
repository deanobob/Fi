/// @file movement_subsystem.hpp
/// @brief The movement subsystem class

#ifndef MOVEMENT_SUBSYSTEM_HPP
#define MOVEMENT_SUBSYSTEM_HPP

#include "camera_controller.hpp"
#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Physics subsystem managing movement of movement components
    class movement_subsystem
        : public core::component_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        movement_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager);
        /// @brief Default destructor
        virtual ~movement_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return true; }
    };
} /// namespace core

#endif /// MOVEMENT_SUBSYSTEM_HPP
