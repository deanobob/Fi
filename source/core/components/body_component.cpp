/// @file body_component.cpp

#include <math.h>
#include "body_component.hpp"
#include "math.hpp"

namespace core
{
    body_component::body_component(const utilities::vector2& position, const utilities::vector2& size, double rotation)
        : m_current_position{position}
        , m_previous_position{position}
        , m_size{size}
        , m_rotation{rotation}
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

    void body_component::set_position(const utilities::vector2& position)
    {
        m_previous_position = m_current_position;
        m_current_position = position;
    }

    void body_component::travel(float distance)
    {
        m_travelled += distance;
    }

    void body_component::set_travelled(float distance)
    {
        m_travelled = distance;
    }

    float body_component::get_travelled() const
    {
        return m_travelled;
    }

    void body_component::move(const utilities::vector2& step)
    {
        m_previous_position = m_current_position;
        m_current_position += step;
    }

    void body_component::rotate(double value, utilities::math::unit_type unit)
    {
        switch (unit)
        {
            case utilities::math::unit_type::degrees:
                m_rotation += utilities::math::to_radians(value);
                break;
            case utilities::math::unit_type::radians:
                m_rotation += value;
                break;
        }
    }

    void body_component::set_rotation(double rotation, utilities::math::unit_type unit)
    {
        switch (unit)
        {
            case utilities::math::unit_type::degrees:
                m_rotation = utilities::math::to_radians(rotation);
                break;
            case utilities::math::unit_type::radians:
                m_rotation = rotation;
                break;
        }
    }

    double body_component::get_rotation() const
    {
        return m_rotation;
    }

    utilities::vector2 body_component::forward() const
    {
        return utilities::vector2::forward(static_cast<float>(m_rotation));
    }

    const utilities::vector2& body_component::get_size() const
    {
        return m_size;
    }
}
