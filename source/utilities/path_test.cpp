/// @file path_test.cpp

#include <cmath>
#include "plog/Log.h"
#include "catch2/catch.hpp"
#include "math.hpp"
#include "vector2.hpp"

TEST_CASE("utilities/path.hpp - Get position at travelled distance along path", "[utilities]")
{
   SECTION("1 Middle of path horizontal")
   {
        const utilities::vector2 start {50, 0};
        const utilities::vector2 end {150, 0};
        const float total_distance {utilities::vector2::distance(start, end)};
        const auto distance_travelled {50.f};
        const auto percentage_travelled {(1.0f / total_distance) * distance_travelled};

        auto position_on_path = utilities::vector2::lerp(start, end, percentage_travelled);
        REQUIRE(position_on_path.x == 100.f);
        REQUIRE(position_on_path.y == 0.f);
   }

   SECTION("1 Middle of path horizontal")
   {
        const utilities::vector2 start {0, 50};
        const utilities::vector2 end {0, 150};
        const float total_distance {utilities::vector2::distance(start, end)};
        const auto distance_travelled {50.f};
        const auto percentage_travelled {(1.0f / total_distance) * distance_travelled};

        auto position_on_path = utilities::vector2::lerp(start, end, percentage_travelled);
        REQUIRE(position_on_path.x == 0.f);
        REQUIRE(position_on_path.y == 100.f);
   }

   SECTION("1 Middle of path diagonal")
   {
        const utilities::vector2 start {50, 50};
        const utilities::vector2 end {150, 150};
        const float total_distance {utilities::vector2::distance(start, end)};
        const auto distance_travelled {50.f};
        const auto percentage_travelled {(1.0f / total_distance) * distance_travelled};

        auto position_on_path = utilities::vector2::lerp(start, end, percentage_travelled);
        REQUIRE(position_on_path.x == 85.35535f);
        REQUIRE(position_on_path.y == 85.35535f);
   }
   
   SECTION("1 Inverted middle of path diagonal")
   {
        const utilities::vector2 start {150, 150};
        const utilities::vector2 end {50, 50};
        const float total_distance {utilities::vector2::distance(start, end)};
        const auto distance_travelled {50.f};
        const auto percentage_travelled {(1.0f / total_distance) * distance_travelled};

        auto position_on_path = utilities::vector2::lerp(start, end, percentage_travelled);
        REQUIRE(position_on_path.x == 114.64465f);
        REQUIRE(position_on_path.y == 114.64465f);
   }
}
