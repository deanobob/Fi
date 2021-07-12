/// @file subsystem.hpp
/// @brief The subsystem base class

#ifndef SUBSYSTEM_HPP
#define SUBSYSTEM_HPP

#include "draw_manager.hpp"
#include "gametime.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for subsystems
    class subsystem :
        public subscriber
    {
        public:
        /// @brief Constructor 
        /// @param p_message_bus Pointer to the message bus instance
        subsystem(message_bus* p_message_bus)
            : mp_message_bus{p_message_bus}
        {}

        /// @brief Default destructor
        virtual ~subsystem() = default;

        /// @brief Initialises the subsystem
        /// @return True if successfully initialised, else false
        virtual bool initialise() = 0;

        /// @brief Called on every tick allowing the subsystem to update
        /// @param gametime The gametime maintaining instance
        virtual void update(const utilities::gametime& gametime) = 0;

        /// @brief Called on every frame to obtain all renderable items
        /// @param renderables Reference to list that will contain all renderables for the current frame
        virtual void draw(std::list<std::tuple<float, float> >& renderables) = 0;

        /// @brief Called when the application is shutting down. Tidy up and clear down.
        virtual void shutdown() = 0;

        /// @brief Getter that indicates if this subsystem is pauseable. Defaults to true.
        /// @return True if pauseable, else false
        virtual bool pauseable() const { return true; }

        protected:
        /// @brief Pointer to the game message bus 
        message_bus* mp_message_bus{nullptr};
    };
} /// namespace core

#endif /// SUBSYSTEM_HPP
