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
        /// @param p_game The game instance
        render_service(core::game* p_game);
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
