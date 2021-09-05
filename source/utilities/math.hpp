/// @file math.hpp
/// @brief Contains math utilities

#ifndef MATH_HPP
#define MATH_HPP

#include <tuple>
#include "vector2.hpp"

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that contains math utilities
    class math
    {
        public:
        /// @brief The rotation unit types
        enum class unit_type : unsigned int
        {
            /// @brief The degrees unit type
            degrees = 0,
            /// @brief The radians unit type
            radians
        };

        /// @brief Clamps a value to a range within the min and max values
        /// @param value The value to clamp
        /// @param min The minimum value
        /// @param max The maximum value
        /// @return The clamped value
        static float clamp(float value, float min, float max);

        /// @brief Converts a rotation in degrees to radians
        /// @param degrees The rotation in degrees
        /// @return The value of degrees in radians
        static double to_radians(double degrees);

        /// @brief Converts a rotation in degrees to radians
        /// @param degrees The rotation in degrees
        /// @return The value of degrees in radians
        static float to_radians(float degrees);

        /// @brief Converts a rotation in radians to degrees
        /// @param radians The rotation in radians
        /// @return The value of radians in degrees
        static double to_degrees(double radians);

        /// @brief Converts a rotation in radians to degrees
        /// @param radians The rotation in radians
        /// @return The value of radians in degrees
        static float to_degrees(float radians);

        /// @brief Linearly interpolate between two values
        /// @param a The start value
        /// @param b The end value
        /// @param t Value between 0 and 1 that defines the value to return
        /// @return The value between a and b
        static float lerp(float a, float b, float t);

        static std::tuple<float, float> cartToIso(float cart_x, float cart_y);

        static utilities::vector2 cartToIso(const utilities::vector2& cart);

        static std::tuple<float, float> isoToCart(float iso_x, float iso_y);

        private:
        /// @brief Default constructor
        math() = default;
        /// @brief Default destructor
        ~math() = default;
    };
} /// namespace utilities

#endif /// MATH_HPP
