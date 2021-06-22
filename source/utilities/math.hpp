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
        /// @brief Clamps a value to a range within the min and max values
        /// @param value The value to clamp
        /// @param min The minimum value
        /// @param max The maximum value
        /// @return The clamped value
        static float clamp(float value, float min, float max);

        private:
        /// @brief Default constructor
        math() = default;
        /// @brief Default destructor
        ~math() = default;
    };
} /// namespace utilities

#endif /// MATH_HPP
