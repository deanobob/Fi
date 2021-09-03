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
        uint8_t r {255};
        /// @param r The green colour value (0 - 255)
        uint8_t g {255};
        /// @param r The blue colour value (0 - 255)
        uint8_t b {255};
        /// @param r The alpha value (0 - 255)
        uint8_t a {255};

        /// @brief Constructor
        /// @param r The red colour value
        /// @param g The green colour value
        /// @param b The blue colour value
        /// @param a The alpha value (defaults to 255)
        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    };
    /// @brief Convenience namespace of pre-defined colours
    namespace colors
    {
        /// @brief The colour white
        static const utilities::color white {255, 255, 255};
        /// @brief The colour black
        static const utilities::color black {0, 0, 0};
        /// @brief The colour red
        static const utilities::color red {255, 0, 0};
        /// @brief The colour green
        static const utilities::color green {0, 255, 0};
        /// @brief The colour blue
        static const utilities::color blue {0, 0, 255};
        /// @brief The colour white
        static const utilities::color yellow {255, 255, 0};
    }

} /// namespace utilities

#endif /// COLOR_HPP
