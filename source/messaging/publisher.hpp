/// @file publisher.hpp
/// @brief Sends messages to subscribers

#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <list>
#include <map>
#include <string>
#include "message.hpp"
#include "subscriber.hpp"

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Class that distributes messages to subscribers
    class publisher
    {
        public:
        /// @brief Default constructor
        publisher() = default;
        /// @brief Default destructor
        ~publisher() = default;

        /// @brief Subscribe for messages from this publisher
        /// @param p_subscriber The subscriber instance
        void subscribe(subscriber* p_subscriber, const std::list<std::string>& message_types);

        /// @brief Unsubscribe from this publisher
        /// @param p_subscriber The subscriber instance
        void unsubscribe(subscriber* p_subscriber, const std::string& message_type);

        /// @brief Publish the message to all subscribers of its type
        /// @param p_message The event args
        void publish(const message* message);

        private:
        /// @brief Container that stores subscribers against the message types they are subscribed to
        std::map<std::string, std::list<subscriber*> > m_subscribers{};
    };
} /// namespace messaging

#endif /// PUBLISHER_HPP
