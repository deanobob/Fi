/// @file entity_manager_test.cpp

#include "catch2/catch.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"

TEST_CASE("core/entity_manager.hpp Entity Manager", "[entity_manager]")
{
    core::entity_manager entity_manager{};

    SECTION("1 Put entity")
    {
        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.get(id) != nullptr);
        REQUIRE(entity_manager.get(id + 1) == nullptr);
    }

    SECTION("2 Get entity by ID")
    {
        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.get(id) != nullptr);
        REQUIRE(entity_manager.get(id + 1) == nullptr);
    }

    SECTION("3 Get entity by tag")
    {
        auto entity = std::make_unique<core::entity>("abcde");
        auto tag = entity->get_tag();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.get(tag) != nullptr);
        REQUIRE(entity_manager.get("not the tag") == nullptr);
    }

    SECTION("4 Remove entity")
    {
        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.remove(id));
        REQUIRE_FALSE(entity_manager.remove(id));
    }
}
