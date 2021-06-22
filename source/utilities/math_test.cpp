/// @file math_test.cpp

#include "catch2/catch.hpp"
#include "math.hpp"

TEST_CASE("utilities/math.hpp - Clamp", "[utilities]")
{
    SECTION("1 Clamp value to maximum")
    {
       REQUIRE(utilities::math::clamp(50, 5, 49) == 49);
    }

    SECTION("2 Clamp value to minimum")
    {
       REQUIRE(utilities::math::clamp(4, 5, 49) == 5);
    }

    SECTION("3 Value within min max range")
    {
       REQUIRE(utilities::math::clamp(5, 5, 49) == 5);
       REQUIRE(utilities::math::clamp(49, 5, 49) == 49);
    }
}
