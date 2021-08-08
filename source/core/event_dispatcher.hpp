/// @file event_dispatcher.hpp
/// @brief Event dispatcher base class

#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include <list>
#include <stdint.h>
#include "event_args.hpp"
#include "event_dispatcher.hpp"
#include "event_handler.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The event dispatcher base class
    class event_dispatcher
    {
        public:
        /// @brief Construct a new event dispatcher object
        /// @param event_type The event type
        event_dispatcher(const event_type& event_type)
            : mp_event_type{event_type}
        {}

        /// @brief Destroy the event dispatcher object
        virtual ~event_dispatcher() {};

        /// @brief Register an event handler
        /// @param p_event_handler Pointer to the event handler
        void register_handler(event_handler* p_event_handler)
        {
            mp_event_handlers.push_back(p_event_handler);
        }

        /// @brief Unregister an event handler
        /// @param p_event_handler Pointer to the event handler
        void unregister_handler(event_handler* p_event_handler)
        {
            mp_event_handlers.remove(p_event_handler);
        }

        /// @brief Dispatch the event with the given arguments 
        /// @param p_event_args The event arguments
        void dispatch(event_args* p_event_args)
        {
            for (auto p_event_handler : mp_event_handlers)
            {
                p_event_handler->on_event_raised(mp_event_type, p_event_args);
            }
        }

        private:
        /// @brief The event type
        const event_type mp_event_type;

        /// @brief List of registered event handlers
        std::list<event_handler*> mp_event_handlers{};

    };
} /// namespace core

#endif /// EVENT_DISPATCHER_HPP