/// @file render_service.hpp
/// @brief Manages rendering the entities and UI

#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP

#include "gametime.hpp"
#include "component_service.hpp"

/// @namespace render namespace
namespace render
{
    /// @brief Manages rendering the game
    class render_service
        : public core::component_service
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Reference to the game message bus
        /// @param p_entity_manager Reference to the entity manager
        render_service(core::message_bus* p_message_bus, core::entity_manager* p_entity_manager);
        /// @brief Destructor
        virtual ~render_service();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager) override;

        void shutdown() override;
    };
} /// namespace render

#endif /// RENDER_SERVICE_HPP
