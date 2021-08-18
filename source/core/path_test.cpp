/// @file math_test.cpp

#include "catch2/catch.hpp"
#include "path_segment_straight.hpp"
#include "path_segment_curved.hpp"

TEST_CASE("core/path_segment*.hpp", "[path_segment]")
{
   SECTION("1 Straight path - end calculations")
   {
      core::path_segment_straight path_segment_right{{0,0}, 0., 50};
      CHECK(path_segment_right.get_end_position().x == Approx(50.).margin(1e-5));
      CHECK(path_segment_right.get_end_position().y == Approx(0.).margin(1e-5));
      CHECK(path_segment_right.get_end_rotation() == 0.0);

      core::path_segment_straight path_segment_down{{0,0}, 90., 50};
      CHECK(path_segment_down.get_end_position().x == Approx(0.).margin(1e-5));
      CHECK(path_segment_down.get_end_position().y == Approx(50.).margin(1e-5));
      CHECK(path_segment_down.get_end_rotation() == 90.0);

      core::path_segment_straight path_segment_left{{0,0}, 180., 50};
      CHECK(path_segment_left.get_end_position().x == Approx(-50.).margin(1e-5));
      CHECK(path_segment_left.get_end_position().y == Approx(0.).margin(1e-5));
      CHECK(path_segment_left.get_end_rotation() == 180.0);

      core::path_segment_straight path_segment_up{{0,0}, 270., 50};
      CHECK(path_segment_up.get_end_position().x == Approx(0.).margin(1e-5));
      CHECK(path_segment_up.get_end_position().y == Approx(-50.).margin(1e-5));
      CHECK(path_segment_up.get_end_rotation() == 270.0);
   }

   SECTION("2 Curved path clockwise - end calculations")
   {
      core::path_segment_curved path_segment_right{{0,0}, 20., 90, 0, true};
      CHECK(path_segment_right.get_end_position().x == Approx(20.).margin(1e-5));
      CHECK(path_segment_right.get_end_position().y == Approx(20.).margin(1e-5));
      CHECK(path_segment_right.get_end_rotation() == Approx(90.0).margin(1e-5));

      core::path_segment_curved path_segment_down{{0,0}, 20., 90, 90, true};
      CHECK(path_segment_down.get_end_position().x == Approx(-20.).margin(1e-5));
      CHECK(path_segment_down.get_end_position().y == Approx(20.).margin(1e-5));
      CHECK(path_segment_down.get_end_rotation() == Approx(180.0).margin(1e-5));

      core::path_segment_curved path_segment_left{{0,0}, 20., 90, 180, true};
      CHECK(path_segment_left.get_end_position().x == Approx(-20.).margin(1e-5));
      CHECK(path_segment_left.get_end_position().y == Approx(-20.).margin(1e-5));
      CHECK(path_segment_left.get_end_rotation() == Approx(270.0).margin(1e-5));

      core::path_segment_curved path_segment_up{{0,0}, 20., 90, 270, true};
      CHECK(path_segment_up.get_end_position().x == Approx(20.).margin(1e-5));
      CHECK(path_segment_up.get_end_position().y == Approx(-20.).margin(1e-5));
      CHECK(path_segment_up.get_end_rotation() == Approx(0.0).margin(1e-5));
   }

   SECTION("3 Curved path anti-clockwise - end calculations")
   {
      core::path_segment_curved path_segment_right{{0,0}, 20., 90, 0, false};
      CHECK(path_segment_right.get_end_position().x == Approx(20.).margin(1e-5));
      CHECK(path_segment_right.get_end_position().y == Approx(-20.).margin(1e-5));
      CHECK(path_segment_right.get_end_rotation() == Approx(90.0).margin(1e-5));

      core::path_segment_curved path_segment_down{{0,0}, 20., 90, 90, false};
      CHECK(path_segment_down.get_end_position().x == Approx(20.).margin(1e-5));
      CHECK(path_segment_down.get_end_position().y == Approx(20.).margin(1e-5));
      CHECK(path_segment_down.get_end_rotation() == Approx(180.0).margin(1e-5));

      core::path_segment_curved path_segment_left{{0,0}, 20., 90, 180, false};
      CHECK(path_segment_left.get_end_position().x == Approx(-20.).margin(1e-5));
      CHECK(path_segment_left.get_end_position().y == Approx(20.).margin(1e-5));
      CHECK(path_segment_left.get_end_rotation() == Approx(270.0).margin(1e-5));

      core::path_segment_curved path_segment_up{{0,0}, 20., 90, 270, false};
      CHECK(path_segment_up.get_end_position().x == Approx(-20.).margin(1e-5));
      CHECK(path_segment_up.get_end_position().y == Approx(-20.).margin(1e-5));
      CHECK(path_segment_up.get_end_rotation() == Approx(0.0).margin(1e-5));
   }
}
