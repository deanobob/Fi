/// @file math.cpp

#include "math.hpp"

namespace utilities
{
    float math::clamp(float value, float min, float max)
    {
        return (value > min) ? (value < max) ? value : max : min;
    }
}
