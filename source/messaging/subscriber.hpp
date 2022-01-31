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
        /// @brief Default constructor
        subscriber() = default;
        /// @brief Default destructor
        virtual ~subscriber() = default;

        /// @brief Overwrite to handle publisher messages
        /// @param message The message
        virtual void on_publish(const message* p_message) = 0;
    };
} /// namespace messaging

#endif /// SUBSCRIBER_HPP