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

    std::tuple<float, float> math::cart_to_iso(float cart_x, float cart_y)
    {
        const auto iso_x = cart_x - cart_y;
        const auto iso_y = (cart_x + cart_y) / 2.f;
        return {iso_x, iso_y};
    }

    utilities::vector2 math::cart_to_iso(const utilities::vector2& cart)
    {
        auto iso_x = cart.x - cart.y;
        auto iso_y = (cart.x + cart.y) / 2.f;
        return {iso_x, iso_y};
    }

    std::tuple<float, float> math::iso_to_cart(float iso_x, float iso_y)
    {
        auto cart_x = (2.f * iso_y + iso_x) / 2.f;
        auto cart_y = (2.f * iso_y - iso_x) / 2.f;
        return {cart_x, cart_y};
    }
}
