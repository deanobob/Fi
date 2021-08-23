/// @file vector2.cpp

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

/// @namespace utilities namespace
namespace utilities
{
    /// @brief A two dimentional vector utility providing methods useful for basic vector math
    class vector2
    {
        public:
        /// @brief A zero vector instance
        static const vector2 ZERO;
        /// @brief A vector instance of value 1
        static const vector2 ONE;
        /// @brief A vector instance of maximum size
        static const vector2 MAX;

        /// @brief The x position
        float x{0};
        /// @brief The y position
        float y{0};

        /// @brief Calculates the distance between two vectors
        /// @param v1 The first vector
        /// @param v2 The second vector
        /// @return The distance between the vectors
        static double distance(const vector2& v1, const vector2& v2);

        /// @brief Calculates the product of two vectors
        /// @param v1 The first vector
        /// @param v2 The second vector
        /// @return The product of the two vectors
        static float dot(const vector2& v1, const vector2& v2);

        /// @brief Normalize the vector
        /// @param vector The vector to normalise
        /// @return The normalised vector
        static vector2 normalise(const vector2& vector);

        /// @brief Clamp a value to the range given by min and max vectors
        /// @param value The value to clamp
        /// @param min The minimum vector value
        /// @param max The maximum vector value
        /// @return The clamped value
        static vector2 clamp(const vector2& value, const vector2& min, const vector2& max);

        /// @brief Get a vector perpendicular to the given vector
        /// @param vector The vector perpendicular to the result
        /// @return A vector perpendicular to the given vector
        static vector2 perp(const vector2& vector);

        /// @brief Linearly interpolate between two points
        /// @param a The start point
        /// @param b The end point
        /// @param t Value between 0 and 1 that defines the point to return
        /// @return The point between a and b
        static vector2 lerp(const vector2& a, const vector2& b, float t);

        /// @brief Get the minimum vector
        /// @param lhs The left-hand side of the operator
        /// @param rhs The right-hand side of the operator
        /// @return The minimum vector
        static vector2 min(const vector2& lhs, const vector2& rhs);

        /// @brief Get the maximum vector
        /// @param lhs The left-hand side of the operator
        /// @param rhs The right-hand side of the operator
        /// @return The maximum vector
        static vector2 max(const vector2& lhs, const vector2& rhs);

        /// @brief Get a vector that can be multiplied by a distance to calculate forward movement at a given angle
        /// @param angle_rad The angle in radians
        /// @return A forward vector
        static vector2 forward(float angle_rad);

        /// @brief Rotate a vector around a centre point by a given angle in radians
        /// @param cx The centre point X coordinate
        /// @param cy The centre point Y coordinate
        /// @param angle_rad The angle to rotate by in radians
        /// @param px The point to rotate X coordinate
        /// @param py The point to rotate Y coordinate
        /// @return The value of pX and pY rotated around the cX and cY position
        static utilities::vector2 rotate_point(float cx, float cy, float angle_rad, float px, float py);

        /// @brief The default constructor
        vector2();

        /// @brief The vector copy constructor
        /// @param vector The vector to copy
        vector2(const vector2& vector);

        /// @brief Constructor that takes an x and y value
        /// @param x The x value
        /// @param y The y value
        vector2(const float x, const float y);

        /// @brief Constructor that takes an x and y value
        /// @param x The x value
        /// @param y The y value
        vector2(const int x, const int y);

        /// @brief The overloaded assignment operator
        /// @param other The vector whose properties will be copied
        /// @return Reference to itself
        vector2& operator=(const utilities::vector2& other);

        /// @brief The overloaded negation operator
        /// @return A copy of vector2 where all values are negated
        vector2 operator-() const;

        /// @brief The overloaded plus operator
        /// @param rhs The other vector whose values will be added to the local vector values
        /// @return A new vector containing the result of the addition operation
        vector2 operator+ (const vector2& rhs) const;

        /// @brief The overloaded plus operator
        /// @param rhs The double value that will be added to the local vectors' properties
        /// @return A new vector containing the result of the addition operation
        vector2 operator+ (const double& rhs) const;

        /// @brief The overloaded plus equals operator
        /// @param rhs The other vector whose values will be added to the local vector
        /// @return The reference to the local vector
        vector2& operator+= (const vector2& rhs);

        /// @brief The overloaded plus equals operator
        /// @param rhs The double value that will be added to the local vectors' properties
        /// @return The reference to the local vector
        vector2& operator+= (const double& rhs);

        /// @brief The overloaded subtract operator
        /// @param rhs The other vector whose values will be subtracted from the local vector values
        /// @return A new vector containing the result of the subtraction operation
        vector2 operator- (const vector2& rhs) const;

        /// @brief The overloaded subtract equals operator
        /// @param rhs The other vector whose values will be subtracted from the local vector
        /// @return The reference to the local vector
        vector2& operator-= (const vector2& rhs);

        /// @brief The overloaded multiply operator
        /// @param rhs The other vector whose values will be multiplied by the local vector values
        /// @return A new vector containing the result of the muliply operation
        vector2 operator* (const vector2& rhs) const;

        /// @brief The overloaded multiply operator
        /// @param rhs The double value that will be multiplied by the local vectors' properties
        /// @return A new vector containing the result of the multiply operation
        vector2 operator* (const double& rhs) const;

        /// @brief The overloaded multiply equals operator
        /// @param rhs The vector that the local vectors' properties will be multiplied by
        /// @return The reference to the local vector
        vector2& operator*= (const vector2& rhs);

        /// @brief The overloaded division operator
        /// @param rhs The other vector whose values will be divided by the local vector values
        /// @return A new vector containing the result of the divide operation
        vector2 operator/ (const vector2& rhs) const;

        /// @brief The overloaded division operator
        /// @param rhs The double value that the local vectors' properties will be divided by
        /// @return A new vector containing the result of the division operation
        vector2 operator/ (const double& rhs) const;

        /// @brief The overloaded division equals operator
        /// @param rhs The double value that the local vectors' properties will be divided by
        /// @return The reference to the local vector
        vector2& operator/= (const vector2& rhs);

        /// @brief The overloaded equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the vector properties match the local vector
        bool operator== (const vector2& rhs) const;

        /// @brief The overloaded not equals operator
        /// @param rhs The right-hand side of the operation
        /// @return True if the vector properties do not match the local vector
        bool operator!= (const vector2& rhs) const;
    };

} /// namespace utilities

#endif /// VECTOR2_HPP
