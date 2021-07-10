/// @file service.hpp
/// @brief The service base class

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "draw_manager.hpp"
#include "gametime.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for services
    class service
    {
        public:
        /// @brief Default destructor
        virtual ~service() = default;

        /// @brief Initialises the service
        /// @return True if successfully initialised, else false
        virtual bool initialise() = 0;

        /// @brief Called on every tick allowing the service to update
        /// @param gametime The gametime maintaining instance
        virtual void update(const utilities::gametime& gametime) = 0;

        /// @brief Called on every frame allowing service to queue drawables
        /// @param draw_manager The draw manager instance
        virtual void draw(draw_manager* p_draw_manager) = 0;

        /// @brief Called when the application is shutting down. Tidy up and clear down.
        virtual void shutdown() = 0;

        /// @brief Getter that indicates if this service is pauseable. Defaults to true.
        /// @return True if pauseable, else false
        virtual bool pauseable() const { return true; }
    };
} /// namespace core

#endif /// SERVICE_HPP
