/// @file publisher.cpp

#include <assert.h>
#include "publisher.hpp"

namespace messaging
{
    void publisher::subscribe(subscriber* p_subscriber, const std::list<std::string>& message_types)
    {
        assert(p_subscriber != nullptr);

        for (const auto& message_type : message_types)
        {
            m_subscribers[message_type].push_back(p_subscriber);
        }
    }

    void publisher::unsubscribe(subscriber* p_subscriber, const std::string& message_type)
    {
        auto it = m_subscribers.find(message_type);
        if (it != m_subscribers.end())
        {
            it->second.remove(p_subscriber);
        }
    }

    void publisher::publish(const message* p_message)
    {
        const auto& subscriber_it = m_subscribers.find(p_message->get_type());
        if (subscriber_it != m_subscribers.end())
        {
            for (const auto& subscriber : subscriber_it->second)
            {
                subscriber->on_publish(p_message);
            }
        }
    }
}
