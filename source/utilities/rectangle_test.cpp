/// @file path_test.cpp

#include <cmath>
#include "plog/Log.h"
#include "catch2/catch.hpp"
#include "rectangle.hpp"

TEST_CASE("utilities/rectangle.hpp - Check intersection", "[utilities]")
{
   SECTION("1 Rectangle intersects another")
   {
        const utilities::rectangle rect1 {0, 0, 50, 50};
        const utilities::rectangle rect2 {25, 25, 50, 50};
        REQUIRE(rect1.intersects(rect2));
        REQUIRE(rect2.intersects(rect1));

        const utilities::rectangle rect3 {-50, -50, 100, 100};
        const utilities::rectangle rect4 {-45, -45, 100, 100};
        REQUIRE(rect1.intersects(rect2));
        REQUIRE(rect2.intersects(rect1));
   }

   SECTION("2 Rectangle contains another")
   {
        const utilities::rectangle rect1 {0, 0, 50, 50};
        const utilities::rectangle rect2 {5, 5, 45, 45};
        REQUIRE(rect1.contains(rect2));
        REQUIRE_FALSE(rect2.contains(rect1));

        const utilities::rectangle rect3 {-50, -50, 100, 100};
        const utilities::rectangle rect4 {-45, -45, 90, 90};
        REQUIRE(rect1.contains(rect2));
        REQUIRE_FALSE(rect2.contains(rect1));
   }
}
