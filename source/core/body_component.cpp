/// @file body_component.cpp

#include "body_component.hpp"

namespace core
{
    body_component::body_component(const utilities::vector2& position, const utilities::vector2& size)
        : m_current_position{position}
        , m_previous_position{position}
        , m_size{size}
    {

    }

    const utilities::vector2& body_component::get_position() const
    {
        return m_current_position;
    }

    const utilities::vector2 body_component::get_interpolated_position(double delta) const
    {
        return m_current_position * delta + m_previous_position * (1.0 - delta);
    }

    void body_component::move(const utilities::vector2& step)
    {
        m_previous_position = m_current_position;
        m_current_position += step;
    }

    const utilities::vector2& body_component::get_size() const
    {
        return m_size;
    }
}
