/// @file publisher.cpp

#include <assert.h>
#include "publisher.hpp"
#include "plog/Log.h"

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

    void publisher::unsubscribe(subscriber* p_subscriber)
    {
        for (auto& subscriber_iter : m_subscribers)
        {
            subscriber_iter.second.remove(p_subscriber);
        }
    }

    void publisher::unsubscribe(subscriber* p_subscriber, const std::string& message_type)
    {
        auto subscriber_iter = m_subscribers.find(message_type);
        if (subscriber_iter != m_subscribers.end())
        {
            subscriber_iter->second.remove(p_subscriber);
        }
    }

    void publisher::publish(const message* p_message)
    {
        const auto& subscriber_iter = m_subscribers.find(p_message->get_type());
        if (subscriber_iter != m_subscribers.end())
        {
            for (const auto& subscriber : subscriber_iter->second)
            {
                subscriber->on_publish(p_message);
            }
        }
    }
}
