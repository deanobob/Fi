/// @file clickable_subsystem.hpp
/// @brief Subsystem that manages user interaction with clickable entities within the simulation 

#ifndef CLICKABLE_SUBSYSTEM_HPP
#define CLICKABLE_SUBSYSTEM_HPP

#include "camera_controller.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"
#include "quadtree.hpp"
#include "quadtree_subsystem.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component subsystems
    class clickable_subsystem
        : public core::quadtree_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        /// @param p_camera_controller The camera controller
        clickable_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager,
            core::camera_controller* p_camera_controller);
        /// @brief Default destructor
        virtual ~clickable_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return true; }

        void on_publish(message* p_message) override;

        private:
        /// @brief Pointer to the camera controller instance
        core::camera_controller* mp_camera_controller{nullptr};
    };
} /// namespace core

#endif /// CLICKABLE_SUBSYSTEM_HPP
