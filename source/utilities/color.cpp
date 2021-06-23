/// @file color.cpp

#include "color.hpp"

namespace utilities
{
    color::color()
        : color(0, 0, 0, 255)
    {

    }

    color::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
}
