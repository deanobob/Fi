/// @file service.hpp
/// @brief The service base class

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "draw_manager.hpp"
#include "gametime.hpp"
#include "resource_manager.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for services
    class service :
        public subscriber
    {
        public:
        /// @brief Constructor 
        /// @param p_message_bus Pointer to the message bus instance
        service(message_bus* p_message_bus)
            : mp_message_bus{p_message_bus}
        {}

        /// @brief Default destructor
        virtual ~service() = default;

        /// @brief Initialises the service
        /// @return True if successfully initialised, else false
        virtual bool initialise() = 0;

        /// @brief Load resources into the game
        /// @param p_resource_manager The resource manager
        virtual void load(core::resource_manager* p_resource_manager) = 0;

        /// @brief Called on every tick allowing the service to update
        /// @param gametime The gametime maintaining instance
        virtual void update(const utilities::gametime& gametime) = 0;

        /// @brief Called on every frame allowing service to queue drawables
        /// @param p_draw_manager The draw manager instance
        /// @param delta The fraction of a frame duration remaining, used to interpolate position of renderables
        virtual void draw(draw_manager* p_draw_manager, double delta) = 0;

        /// @brief Called when the application is shutting down. Tidy up and clear down.
        virtual void shutdown() = 0;

        /// @brief Getter that indicates if this service is pauseable. Defaults to true.
        /// @return True if pauseable, else false
        virtual bool pauseable() const { return true; }

        protected:
        /// @brief Pointer to the game message bus 
        message_bus* mp_message_bus{nullptr};
    };
} /// namespace core

#endif /// SERVICE_HPP
