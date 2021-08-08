/// @file message_bus.hpp
/// @brief Manages distribution of messages across all subscribers

#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <list>
#include <map>
#include <string>
#include "message.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Class that distributes messages to subscribers
    class message_bus
    {
        public:
        /// @brief Subscribe for messages from this message_bus
        /// @param p_subscriber The subscriber instance
        /// @param message_types The message types the subscriber is interested in
        void subscribe(subscriber* p_subscriber, const std::list<std::string>& message_types);

        /// @brief Unsubscribe all messages from this message_bus
        /// @param p_subscriber The subscriber instance
        void unsubscribe(subscriber* p_subscriber);

        /// @brief Unsubscribe a single message type from this message_bus
        /// @param p_subscriber The subscriber instance
        /// @param message_type The message type
        void unsubscribe(subscriber* p_subscriber, const std::string& message_type);

        /// @brief Send the message to all subscribers that have registered for that specific message
        /// @param p_message The event args
        void send(message* p_message);

        private:
        /// @brief Container that stores subscribers against the message types they are subscribed to
        std::map<const std::string, std::list<subscriber*> > m_subscribers{};
    };
} /// namespace core

#endif /// MESSAGE_BUS_HPP
