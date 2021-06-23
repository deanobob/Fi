/// @file rectangle.hpp

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "point.hpp"
#include "vector2.hpp"

/// @namespace utilities namespace
namespace utilities
{
    /// @brief A utility that represents a rectangle object
    class rectangle
    {
        public:
        /// @brief An empty rectangle instance (position 0,0 size 0)
        static const rectangle EMPTY;

        /// @brief The x position
        float x{0};
        /// @brief The x position
        float y{0};
        /// @brief The width
        float width{0};
        /// @brief The height
        float height{0};

        /// @brief The default constructor
        rectangle();
        /// @brief Constructor that generates the object with the given x, y, width, and height values
        /// @param x The x position
        /// @param y The y position
        /// @param width The width
        /// @param height The height
        rectangle(float x, float y, float width, float height);

        /// @brief Gets the position of the top-left of the rectangle
        /// @return The position of the top-left of the rectangle as a vector2
        vector2 get_position() const;

        /// @brief Get the position of the left side of the rectangle
        /// @return The position of the left side of the rectangle
        float get_left() const;

        /// @brief Get the position of the right side of the rectangle
        /// @return The position of the right side of the rectangle
        float get_right() const;

        /// @brief Get the position of the top side of the rectangle
        /// @return The position of the top side of the rectangle
        float get_top() const;

        /// @brief Get the position of the bottom side of the rectangle
        /// @return The position of the bottom side of the rectangle
        float get_bottom() const;

        /// @brief Get the position of the centre of the rectangle
        /// @return The position of the centre of the rectangle as a vector2
        vector2 get_centre() const;

        /// @brief Get the x position of the centre of the rectangle
        /// @return The x position of the centre of the rectangle
        float get_centre_x() const;

        /// @brief Get the y position of the centre of the rectangle
        /// @return The y position of the centre of the rectangle
        float get_centre_y() const;

        /// @brief Check if the given x and y coordinates are within the bounds of the rectangle
        /// @param x The x coordinate
        /// @param y The y coordinate
        /// @return True if within the bounds
        bool contains(float x, float y) const;

        /// @brief Check if the given point is within the bounds of the rectangle
        /// @param value The point object
        /// @return True if within the bounds
        bool contains(const point& value) const;

        /// @brief Check if the given vector2 is within the bounds of the rectangle
        /// @param value The vector2 object
        /// @return True if within the bounds
        bool contains(const vector2& value) const;

        /// @brief Check if the given rectangle is within the bounds of the rectangle
        /// @param value The rectangle object
        /// @return True if within the bounds
        bool contains(const rectangle& value) const;

        /// @brief Check if the given rectangle overlaps the bounds of the rectangle
        /// @param value The rectangle object
        /// @return True if any part of the given rectangle overlaps the local rectangle
        bool intersects(const rectangle& value) const;

        /// @brief The overloaded equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the rectangle properties match the local rectangle
        bool operator== (const rectangle& rhs) const;

        /// @brief The overloaded not equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the rectangle properties do not match the local rectangle
        bool operator!= (const rectangle& rhs) const;
    };
} /// namespace utilities

#endif /// RECTANGLE_HPP
