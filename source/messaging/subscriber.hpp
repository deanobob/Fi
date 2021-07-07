/// @file subscriber.hpp
/// @brief Handles messages from publishers

#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "message.hpp"
#include "subscriber.hpp"

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Class that distributes messages to subscribers
    class subscriber
    {
        public:
        /// @brief Default destructor
        virtual ~subscriber() = default;

        /// @brief Overwrite to handle publisher messages
        /// @param p_message The message
        virtual void on_publish(message* p_message) = 0;
    };
} /// namespace messaging

#endif /// SUBSCRIBER_HPP
