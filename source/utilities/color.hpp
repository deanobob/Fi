/// @file color.hpp

#ifndef COLOR_HPP
#define COLOR_HPP

#include <inttypes.h>

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Utility that contains an RGBA colour definition
    class color
    {
        public:
        /// @param r The red colour value (0 - 255)
        const uint8_t r;
        /// @param r The green colour value (0 - 255)
        const uint8_t g;
        /// @param r The blue colour value (0 - 255)
        const uint8_t b;
        /// @param r The alpha value (0 - 255)
        const uint8_t a;

        /// @brief Constructor
        /// @param r The red colour value
        /// @param g The green colour value
        /// @param b The blue colour value
        /// @param a The alpha value (defaults to 255)
        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    };
} /// namespace utilities

#endif /// COLOR_HPP
