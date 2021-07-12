/// @file render_subsystem.hpp
/// @brief The component service base class

#ifndef RENDER_SUBSYSTEM_HPP
#define RENDER_SUBSYSTEM_HPP

#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component subsystems
    class render_subsystem
        : public core::component_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        render_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager);
        /// @brief Default destructor
        virtual ~render_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(std::list<std::tuple<float, float> >& renderables) override;

        void shutdown() override;

        bool pauseable() const override { return true; }
    };
} /// namespace core

#endif /// RENDER_SUBSYSTEM_HPP