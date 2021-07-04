/// @file input.hpp

#ifndef INPUT_HPP
#define INPUT_HPP

#include <list>
#include "input_event_listener.hpp"

/// @namespace framework namespace
namespace framework
{
    /// @brief The input class
    class input
    {
        public:
        /// @brief flags - converted from SDL as required
        static constexpr auto FLAGS_WINDOW_OPENGL = 2;

        /// @brief Add a input event listener
        /// @param p_event_listener The event listener
        void add_event_listener(input_event_listener* p_event_listener)
        {
            mp_event_listeners.push_back(p_event_listener);
        }

        /// @brief Remove a input event listener
        /// @param p_event_listener The event listener
        void remove_event_listener(input_event_listener* p_event_listener)
        {
            mp_event_listeners.remove(p_event_listener);
        }

        /// @brief Initialise input
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

} /// namespace framework

#endif /// INPUT_HPP
