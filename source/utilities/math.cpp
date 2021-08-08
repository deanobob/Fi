/// @file math.cpp

#include <math.h>
#include "math.hpp"

namespace utilities
{
    float math::clamp(float value, float min, float max)
    {
        return (value > min) ? (value < max) ? value : max : min;
    }

    double math::to_radians(double value)
    {
        return value * M_PI / 180.0;
    }

    float math::to_radians(float value)
    {
        return value * M_PI / 180.0f;
    }
}
