/// @file publisher.hpp
/// @brief Sends messages to subscribers

#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <list>
#include <string>
#include "event_args.hpp"
#include "subscriber.hpp"

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Class that distributes messages to subscribers
    class publisher
    {
        public:
        /// @brief Constructor
        publisher(const std::string& event_id);
        /// @brief Default destructor
        ~publisher() = default;

        /// @brief Subscribe for messages from this publisher
        /// @param p_subscriber The subscriber instance
        void subscribe(subscriber* p_subscriber);

        /// @brief Unsubscribe from this publisher
        /// @param p_subscriber The subscriber instance
        void unsubscribe(subscriber* p_subscriber);

        /// @brief Publish the event
        /// @param p_event_args The event args
        void publish(const event_args* p_event_args = nullptr);

        private:
        /// @brief The event ID
        const std::string m_event_id;
        /// @brief Container for the subscribers
        std::list<subscriber*> m_subscribers{};
    };
} /// namespace messaging

#endif /// PUBLISHER_HPP
