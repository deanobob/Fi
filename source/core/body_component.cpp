/// @file body_component.cpp

#include "body_component.hpp"

namespace core
{
    body_component::body_component(const utilities::vector2& position, const utilities::vector2& size)
        : m_position{position}
        , m_size{size}
    {

    }

    const utilities::vector2& body_component::get_position() const
    {
        return m_position;
    }
    
    void body_component::move(const utilities::vector2& step)
    {
        m_position += step;
    }

    const utilities::vector2& body_component::get_size() const
    {
        return m_size;
    }
}
