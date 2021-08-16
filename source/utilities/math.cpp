/// @file math.cpp

#include <math.h>
#include "math.hpp"

namespace utilities
{
    float math::clamp(float value, float min, float max)
    {
        return (value > min) ? (value < max) ? value : max : min;
    }

    double math::to_radians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    float math::to_radians(float degrees)
    {
        return degrees * static_cast<float>(M_PI) / 180.0f;
    }

    double math::to_degrees(double radians)
    {
        return radians * (180.0 / M_PI);
    }

    float math::to_degrees(float radians)
    {
        return radians * (180.0f / static_cast<float>(M_PI));
    }

    float math::lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }
}
