/// @file path_segment_curved.hpp
/// @brief The curved path segment

#ifndef PATH_SEGMENT_CURVED_HPP
#define PATH_SEGMENT_CURVED_HPP

#include <math.h>
#include "plog/Log.h"
#include "math.hpp"
#include "path_segment.hpp"
#include "vector2.hpp"

/// @namespace core namespace
namespace core
{
    /// @class The curved path segment
    class path_segment_curved :
        public path_segment
    {
        public:
        /// @brief Construct a new path segment curved object
        /// @param start The start of the segment 
        /// @param radius The radius of the circle
        /// @param angle The angle of the segment in degrees
        /// @param start_angle The angle offset, defines which angle to begin the path
        path_segment_curved(const utilities::vector2& start, float radius, float angle, float start_angle = 0.0f)
            : m_start{start}
            , m_radius{radius}
            , m_start_angle{utilities::math::to_radians(start_angle)}
            , m_angle{angle}
            , m_centre{m_start + utilities::vector2::forward(m_start_angle) * radius}
            , m_length{(m_angle / 360.f) * M_PI * (m_radius * 2.0)}
            , m_end{get_position_at(m_length)}
        {
            
        }

        const utilities::vector2& get_start_position() const override
        {
            return m_start;
        }

        const utilities::vector2& get_end_position() const override
        {
            return m_end;
        }

        const utilities::vector2 get_position_at(double distance) const override
        {
            // Calculate the total percentage of 
            const auto angle_travelled {(m_angle / m_length) * distance};
            // Calculate the location on the arc at the given angle plus offset
            const auto position_angle {m_start_angle + utilities::math::to_radians(angle_travelled - 180.f)};
            return utilities::vector2{
                static_cast<float>(m_centre.x + m_radius * cos(position_angle)), 
                static_cast<float>(m_centre.y + m_radius * sin(position_angle))};
        }

        double length() const override
        {
            return m_length;
        }

        private:
        /// @brief The path start point
        const utilities::vector2 m_start;
        /// @brief The angle of the path
        const float m_radius;
        /// @brief The angle offset
        const float m_start_angle;
        /// @brief The angle that defines the length of the arc
        const float m_angle;
        /// @brief The centre of the circle that forms the arc
        const utilities::vector2 m_centre;
        /// @brief The length of the path
        const double m_length;
        /// @brief The path end point
        const utilities::vector2 m_end;
    };

} /// namespace core

#endif /// PATH_SEGMENT_HPP