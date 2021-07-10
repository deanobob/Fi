/// @file render_service.hpp
/// @brief Manages rendering the entities and UI

#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP

#include "gametime.hpp"
#include "component_service.hpp"

/// @namespace core namespace
namespace core
{
    /// Forward declarations
    class game;
}

/// @namespace services namespace
namespace services
{
    /// @brief Manages rendering the game
    class render_service
        : public core::component_service
    {
        public:
        /// @brief Constructor
        /// @param message_bus Reference to the game message bus
        /// @param entity_manager Reference to the entity manager
        render_service(core::message_bus& message_bus, core::entity_manager& entity_manager);
        /// @brief Destructor
        virtual ~render_service();

        core::service_type get_type() const override
        {
            return core::service_type::render_service;
        }

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void shutdown() override;
    };
} /// namespace services

#endif /// RENDER_SERVICE_HPP
