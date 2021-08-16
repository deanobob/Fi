/// @file path_segment.hpp
/// @brief The base class for path segments

#ifndef PATH_SEGMENT_HPP
#define PATH_SEGMENT_HPP

#include "vector2.hpp"

/// @namespace core namespace
namespace core
{
    /// @class The base class for path segments
    class path_segment
    {
        public:
        /// @brief Destroy the path segment object
        virtual ~path_segment() = default;

        /// @brief Get the start of the segment
        /// @return The start of the segment
        virtual const utilities::vector2& get_start_position() const = 0;

        /// @brief Get the end of the segment
        /// @return The end of the segment
        virtual const utilities::vector2& get_end_position() const = 0; 

        /// @brief Get the coordinates of the point on the path at distance
        /// @param distance The distance travelled on the route
        /// @return The position at a given distance along the route
        virtual const utilities::vector2 get_position_at(double distance) const = 0;

        virtual double get_start_rotation() const = 0;

        virtual double get_end_rotation() const = 0; 

        virtual double get_rotation_at(double distance) const = 0;

        /// @brief Get the total length of the path segment
        /// @return The total length
        virtual double length() const = 0;
    };

} /// namespace core

#endif /// PATH_SEGMENT_HPP