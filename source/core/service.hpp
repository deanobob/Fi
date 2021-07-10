/// @file service.hpp
/// @brief The service base class

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "gametime.hpp"
#include "service_type.hpp"
#include "system_interface.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Forward declare game class
    class game;

    /// @brief Base class for services
    class service
    {
        public:
        /// @param default destructor
        virtual ~service() = default;

        /// @brief Get the service type
        /// @return The service type
        virtual service_type get_type() const = 0;

        /// @brief Initialises the service
        /// @return True if successfully initialised, else false
        virtual bool initialise() = 0;

        /// @brief Called on every tick allowing the service to update
        /// @param gametime The gametime maintaining instance
        virtual void update(const utilities::gametime& gametime) = 0;

        /// @brief Called when the application is shutting down. Tidy up and clear down.
        virtual void shutdown() = 0;

        /// @brief Getter that indicates if this service is pauseable. Defaults to true.
        /// @return True if pauseable, else false
        virtual bool pauseable() const { return true; }
    };
} /// namespace core

#endif /// SERVICE_HPP
