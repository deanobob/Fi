/// @file input_controller.hpp

#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

#include <list>
#include "input_event_listener.hpp"

/// @namespace input namespace
namespace input
{
    /// @brief The input_controller class
    class input_controller
    {
        public:
        /// @brief Add a input_controller event listener
        /// @param p_event_listener The event listener
        void add_event_listener(input_event_listener* p_event_listener)
        {
            mp_event_listeners.push_back(p_event_listener);
        }

        /// @brief Remove a input_controller event listener
        /// @param p_event_listener The event listener
        void remove_event_listener(input_event_listener* p_event_listener)
        {
            mp_event_listeners.remove(p_event_listener);
        }

        /// @brief Initialise input controller
        /// @return True on success, false if failed to initialise
        virtual bool initialise() = 0;

        /// @brief Process events from input sources
        virtual void process_events() = 0;

        /// @brief Terminates all input sources
        virtual void shutdown() = 0;

        protected:
        /// @brief Container for event listeners subscribed to receive display events
        std::list<input_event_listener*> mp_event_listeners{};
    };

} /// namespace input

#endif /// INPUT_CONTROLLER_HPP
