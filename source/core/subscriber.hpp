/// @file subscriber.hpp
/// @brief Handles messages from message_bus

#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "message.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Class that distributes messages to subscribers
    class subscriber
    {
        public:
        /// @brief Default destructor
        virtual ~subscriber() = default;

        /// @brief Overwrite to handle message_bus messages
        /// @param p_message The message
        virtual void on_publish(message* p_message) = 0;
    };
} /// namespace core

#endif /// SUBSCRIBER_HPP
