/// @file point.hpp
/// @brief Contains a utility for representing a point in 2d space

#ifndef POINT_HPP
#define POINT_HPP

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that represents a point in 2d space
    class point
    {
        public:
        /// @brief An instance of point at position zero, zero
        static const point ZERO;
        /// @brief An instance of point at position one, one
        static const point ONE;

        /// @brief The x position
        int x {0};
        /// @brief The y position
        int y {0};

        /// @brief Constructor that initialises the point at zero, zero
        point();
        /// @brief Constructor that initialises the point at a given point
        /// @param value The point to copy
        point(const point& value);
        /// @brief Constructor that initialises the point at a given x and y coordinate
        /// @param x The x position
        /// @param y The y position
        point(const int x, const int y);

        /// @brief The overloaded plus operator
        /// @param rhs The other point whose values will be added to the local point values
        /// @return A new point containing the result of the addition operation
        point operator+ (const point& rhs) const;

        /// @brief The overloaded plus equals operator
        /// @param rhs The other point whose values will be added to the local point
        /// @return The reference to the local point
        point& operator+= (const point& rhs);

        /// @brief The overloaded subtract operator
        /// @param rhs The other point whose values will be subtracted from the local point values
        /// @return A new point containing the result of the subtraction operation
        point operator- (const point& rhs) const;

        /// @brief The overloaded subtract equals operator
        /// @param rhs The other point whose values will be subtracted from the local point
        /// @return The reference to the local point
        point& operator-= (const point& rhs);

        /// @brief The overloaded multiply operator
        /// @param rhs The other point whose values will be multiplied by the local point values
        /// @return A new point containing the result of the muliply operation
        point operator* (const point& rhs) const;

        /// @brief The overloaded multiply equals operator
        /// @param rhs The point that the local points' properties will be multiplied by
        /// @return The reference to the local point
        point& operator*= (const point& rhs);

        /// @brief The overloaded division operator
        /// @param rhs The other point whose values will be divided by the local point values
        /// @return A new point containing the result of the divide operation
        point operator/ (const point& rhs) const;

        /// @brief The overloaded division equals operator
        /// @param rhs The double value that the local points' properties will be divided by
        /// @return The reference to the local point
        point& operator/= (const point& rhs);

        /// @brief The overloaded equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the point properties match the local point
        bool operator== (const point& rhs) const;

        /// @brief The overloaded not equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the point properties do not match the local point
        bool operator!= (const point& rhs) const;
    };
} /// namespace utilities

#endif /// POINT_HPP
