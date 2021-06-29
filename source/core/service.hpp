/// @file service.hpp
/// @brief The service base class

#ifndef SERVICE_HPP
#define SERVICE_HPP

#include "gametime.hpp"
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
        /// @brief Constructor
        /// @param p_game The game instance
        service(game* p_game);
        /// @brief Default destructor
        virtual ~service() = default;

        /// @brief Get the framework system interface
        /// @return Reference to the framework system interface
        framework::system_interface* get_system_interface();

        /// @brief Initialises the service
        /// @return True if successfully initialised, else false
        virtual bool initialise() = 0;
        /// @brief Called on every tick allowing the service to update
        /// @param gametime The gametime maintaining instance
        virtual void update(utilities::gametime& gametime) = 0;
        /// @brief Called when the application is shutting down. Tidy up and clear down.
        virtual void shutdown() = 0;
        /// @brief Getter that indicates if this service is pauseable. Defaults to true.
        /// @return True if pauseable, else false
        virtual bool pauseable() const { return true; }

        protected:
        /// @brief Pointer to the instance of the game
        game* mp_game {nullptr};
    };
} /// namespace core

#endif /// SERVICE_HPP
