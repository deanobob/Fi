/// @file path_segment_straight.hpp
/// @brief The straight path segment

#ifndef PATH_SEGMENT_STRAIGHT_HPP
#define PATH_SEGMENT_STRAIGHT_HPP

#include "math.hpp"
#include "path_segment.hpp"
#include "vector2.hpp"

/// @namespace core namespace
namespace core
{
    /// @class The straight path segment
    class path_segment_straight :
        public path_segment
    {
        public:
        /// @brief Construct a new path segment straight object
        /// @param start The start of the segment 
        /// @param angle The angle of the segment in degrees
        /// @param length The length of the segment 
        path_segment_straight(const utilities::vector2& start, float angle, float length)
            : m_start{start}
            , m_angle_rad{utilities::math::to_radians(angle)}
            , m_length{length}
            , m_end{get_position_at(length)}
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
            return m_start + utilities::vector2::forward(m_angle_rad) * distance;
        }

        double get_start_rotation() const override
        {
            return utilities::math::to_degrees(m_angle_rad);
        }

        double get_end_rotation() const override
        {
            return utilities::math::to_degrees(m_angle_rad);
        } 

        double get_rotation_at(double distance) const override
        {
            return m_angle_rad;
        }

        double length() const override
        {
            return m_length;
        }

        private:
        /// @brief The origin of the path
        const utilities::vector2 m_start;
        /// @brief The path angle in radians
        const float m_angle_rad;
        /// @brief The length of the path
        const float m_length;
        /// @brief The end of the path
        const utilities::vector2 m_end;
    };

} /// namespace core

#endif /// PATH_SEGMENT_HPP