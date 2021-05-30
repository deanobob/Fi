/// @file publisher.cpp

#include <assert.h>
#include "publisher.hpp"

namespace messaging
{
    publisher::publisher(const std::string& event_id) :
        m_event_id{event_id}
    {

    }

    void publisher::subscribe(subscriber* p_subscriber)
    {
        assert(p_subscriber != nullptr);
        m_subscribers.push_back(p_subscriber);
    }

    void publisher::unsubscribe(subscriber* p_subscriber)
    {
        m_subscribers.remove(p_subscriber);
    }

    void publisher::publish(const event_args* p_event_args)
    {
        for (const auto& subscriber : m_subscribers)
        {
            subscriber->on_publish(m_event_id, p_event_args);
        }
    }
}
