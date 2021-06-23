/// @file color.hpp

#ifndef COLOR_HPP
#define COLOR_HPP

#include <inttypes.h>

namespace utilities
{
    class color
    {
        public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        color();
        color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    };
} /// namespace utilities

#endif /// COLOR_HPP
