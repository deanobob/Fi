/// @file vector2_test.cpp

#include "catch2/catch.hpp"
#include "vector2.hpp"

TEST_CASE("utilities/vector2.hpp - Vector2", "[utilities]")
{
   SECTION("1 Create vector2")
   {
      utilities::vector2 vector2{};
      REQUIRE(vector2 == utilities::vector2::ZERO);

      vector2 = utilities::vector2{5, 10};
      REQUIRE(vector2.x == 5);
      REQUIRE(vector2.y == 10);

      vector2 = utilities::vector2{vector2};
      REQUIRE(vector2.x == 5);
      REQUIRE(vector2.y == 10);
   }

   SECTION("2 Vector2 distance")
   {
      utilities::vector2 v1{5, 5};
      utilities::vector2 v2{10, 5};
      REQUIRE(utilities::vector2::distance(v1, v2) == 5.0);

      utilities::vector2 v3{5, 15};
      REQUIRE(utilities::vector2::distance(v1, v3) == 10.0);
   }
}
