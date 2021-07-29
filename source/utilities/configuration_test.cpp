/// @file configuration_test.cpp

#include "catch2/catch.hpp"
#include "configuration.hpp"

TEST_CASE("utilities/configuration.hpp - Add and get", "[utilities]")
{
   utilities::configuration config;
   SECTION("1 Add configuration and get as string")
   {
      config.add("Key1", "Val1");
      REQUIRE(config.get_string("Key1") == "Val1");
   }

   SECTION("2 Add configuration and get as integer")
   {
      config.add("Key2", "7");
      REQUIRE(config.get_int("Key2") == 7);
   }

   SECTION("3 Add configuration and get as float")
   {
      config.add("Key3", "7.4");
      REQUIRE(config.get_float("Key3") == 7.4f);
   }

   SECTION("4 Add configuration and get as double")
   {
      config.add("Key4", "7.1");
      REQUIRE(config.get_double("Key4") == 7.1);
   }

   SECTION("5 Add configuration and get as boolean")
   {
      config.add("Key5", "true");
      REQUIRE(config.get_bool("Key5"));

      config.add("Key6", "false");
      REQUIRE_FALSE(config.get_bool("Key6"));
   }
}
