/// @file subscriber.hpp
/// @brief Handles messages from publishers

#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "event_args.hpp"
#include "subscriber.hpp"

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Class that distributes messages to subscribers
    class subscriber
    {
        public:
        /// @brief Default constructor
        subscriber() = default;
        /// @brief Default destructor
        virtual ~subscriber() = default;

        /// @brief Overwrite to handle publisher messages
        /// @param event_id The event ID
        /// @param event_args The event arguments
        virtual void on_publish(const std::string& event_id, const event_args* p_event_args) = 0;
    };
} /// namespace messaging

#endif /// SUBSCRIBER_HPP
