/// @file map_subsystem.hpp
/// @brief Subsystem that manages the map

#ifndef MAP_SUBSYSTEM_HPP
#define MAP_SUBSYSTEM_HPP

#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component subsystems
    class map_subsystem
        : public core::component_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        map_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager);
        /// @brief Default destructor
        virtual ~map_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return true; }


        private:
        uint8_t m_map[25] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    };
} /// namespace core

#endif /// MAP_SUBSYSTEM_HPP
