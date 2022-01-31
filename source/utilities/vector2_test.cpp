/// @file vector2_test.cpp

#include "catch2/catch.hpp"
#include "math.hpp"
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

   SECTION("3 Vector2 forward")
   {
      auto forward_value = utilities::vector2::forward(utilities::math::to_radians(0.));
      CHECK(forward_value.x == Approx(1.).margin(1e-5));
      CHECK(forward_value.y == Approx(0.).margin(1e-5));

      forward_value = utilities::vector2::forward(utilities::math::to_radians(90.));
      CHECK(forward_value.x == Approx(0.).margin(1e-5));
      CHECK(forward_value.y == Approx(1.).margin(1e-5));

      forward_value = utilities::vector2::forward(utilities::math::to_radians(180.));
      CHECK(forward_value.x == Approx(-1.).margin(1e-5));
      CHECK(forward_value.y == Approx(0.).margin(1e-5));

      forward_value = utilities::vector2::forward(utilities::math::to_radians(270.));
      CHECK(forward_value.x == Approx(0.).margin(1e-5));
      CHECK(forward_value.y == Approx(-1.).margin(1e-5));
   }
}
