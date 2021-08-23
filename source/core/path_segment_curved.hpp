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
    /// @brief The path_segment_curved class
    class path_segment_curved :
        public path_segment
    {
        public:
        /// @brief Construct a new path segment curved object
        /// @param start The start of the segment 
        /// @param radius The radius of the circle
        /// @param angle_deg The angle of the segment in degrees
        /// @param start_angle_deg The angle offset, defines which angle to begin the path
        /// @param clockwise Whether to curve clockwise or anti-clockwise from start position
        path_segment_curved(const utilities::vector2& start, 
                            float radius, 
                            float angle_deg, 
                            float start_angle_deg = 0.0f, 
                            bool clockwise = true)
            : m_start{start}
            , m_clockwise{clockwise}
            , m_radius{radius}
            , m_start_angle_rad{utilities::math::to_radians(start_angle_deg)}
            , m_angle_rad{utilities::math::to_radians(angle_deg)}
            , m_centre{m_clockwise 
                        ? m_start + utilities::vector2::forward(static_cast<float>(M_PI / 2.0) + m_start_angle_rad) * radius
                        : m_start - utilities::vector2::forward(static_cast<float>(M_PI / 2.0) + m_start_angle_rad) * radius}
            , m_length{(angle_deg / 360.f) * M_PI * (m_radius * 2.0)}
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
            // Calculate the location on the arc at the given angle plus offset
            const auto position_angle_rad {get_rotation_at(distance) - (M_PI / 2.0)};
            return utilities::vector2{
                static_cast<float>(m_centre.x + m_radius * cos(position_angle_rad)), 
                static_cast<float>(m_centre.y + m_radius * sin(position_angle_rad))};
        }

        double get_start_rotation() const override
        {
            return utilities::math::to_degrees(get_rotation_at(0.0f));
        }

        double get_end_rotation() const override
        {
            auto rotation_rad = get_rotation_at(m_length);
            if (!m_clockwise)
            {
                rotation_rad += M_PI;
            }
            return std::fmod(utilities::math::to_degrees(rotation_rad), 360.0);
        } 

        double get_rotation_at(double distance) const override
        {
            // Calculate the total percentage of angle travelled
            auto angle_travelled_rad {(m_angle_rad / m_length) * distance};
            if (!m_clockwise)
            {
                // Invert angle travelled to move counter clockwise
                angle_travelled_rad = m_angle_rad - angle_travelled_rad + M_PI - m_angle_rad;
            }

            return m_start_angle_rad + angle_travelled_rad;
        }

        double length() const override
        {
            return m_length;
        }

        private:
        /// @brief The path start point
        const utilities::vector2 m_start;
        /// @brief The direction from start the curve will move in
        const bool m_clockwise;
        /// @brief The angle of the path
        const float m_radius;
        /// @brief The angle offset in radians
        const float m_start_angle_rad;
        /// @brief The angle that defines the length of the arc in radians
        const float m_angle_rad;
        /// @brief The centre of the circle that forms the arc
        const utilities::vector2 m_centre;
        /// @brief The length of the path
        const double m_length;
        /// @brief The path end point
        const utilities::vector2 m_end;
    };

} /// namespace core

#endif /// PATH_SEGMENT_HPP