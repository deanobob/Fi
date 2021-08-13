/// @file math.hpp
/// @brief Contains math utilities

#ifndef MATH_HPP
#define MATH_HPP

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

        static float lerp(float a, float b, float t);

        private:
        /// @brief Default constructor
        math() = default;
        /// @brief Default destructor
        ~math() = default;
    };
} /// namespace utilities

#endif /// MATH_HPP
