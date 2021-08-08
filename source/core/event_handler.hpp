/// @file event_handler.hpp
/// @brief Event handler base class

#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <stdint.h>
#include "event_args.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Alias for event type
    using event_type = std::string;

    /// @brief The event handler base class
    class event_handler
    {
        public:
        /// @brief Called when an event is raised
        /// @param event_type The type of event that has been raised
        /// @param p_event_args The event arguments
        virtual void on_event_raised(const event_type& event_type, event_args* p_event_args) = 0;
    };
} /// namespace core

#endif /// EVENT_HANDLER_HPP