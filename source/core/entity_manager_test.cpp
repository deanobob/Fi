/// @file bob_test.cpp

// #include <map>
#include "catch2/catch.hpp"
#include "component.hpp"
#include "entity_manager.hpp"

/// @brief A test component
class test_component : public core::component
{
    public:
    /// @brief Get the component type
    /// @return The component type
    core::component_type get_type() const override
    {
        return core::component_type::body;
    }

    /// @brief Increment the counter
    void increment_counter()
    {
        m_test_counter++;
    }

    /// @brief Get the counter value
    /// @return The counter value
    uint32_t get_count() const
    {
        return m_test_counter;
    }


    private:
    /// @brief The test counter
    uint32_t m_test_counter{0};
};

TEST_CASE("core/entity_manager.hpp Entity Manager", "[entity_manager]")
{
    core::entity_manager entity_manager{};

    SECTION("Create entity")
    {
        core::entity_id eid = entity_manager.create_entity();
        REQUIRE(eid == 1);
        eid = entity_manager.create_entity();
        REQUIRE(eid == 2);
    }

    SECTION("Delete entity")
    {
        core::entity_id eid = entity_manager.create_entity();
        REQUIRE(eid == 1);
        REQUIRE(entity_manager.delete_entity(eid));
        REQUIRE_FALSE(entity_manager.delete_entity(eid));
    }

    SECTION("Add component")
    {
        // Create entity
        core::entity_id eid = entity_manager.create_entity();
        REQUIRE(eid == 1);

        // Add component
        REQUIRE(entity_manager.add_component(std::make_unique<test_component>(), eid));

        // Check component added
        REQUIRE(entity_manager.get_component<test_component>(core::component_type::body, eid) != nullptr);
        // Check get non-existent component fails
        REQUIRE_FALSE(entity_manager.get_component<test_component>(core::component_type::render, eid) != nullptr);
    }

    SECTION("Get component allows modification of component")
    {
        // Create entity
        core::entity_id eid = entity_manager.create_entity();
        REQUIRE(eid == 1);

        // Add component
        REQUIRE(entity_manager.add_component(std::make_unique<test_component>(), eid));

        // Check test component returned and counter increments
        auto component = entity_manager.get_component<test_component>(core::component_type::body, eid);
        REQUIRE(component != nullptr);
        REQUIRE(component->get_count() == 0);
        component->increment_counter();
        REQUIRE(component->get_count() == 1);

        // Check test component returned with updated counter and continues to increment
        component = entity_manager.get_component<test_component>(core::component_type::body, eid);
        REQUIRE(component != nullptr);
        REQUIRE(component->get_count() == 1);
        component->increment_counter();
        REQUIRE(component->get_count() == 2);
    }

    SECTION("Remove component")
    {
        // Create entity
        core::entity_id eid = entity_manager.create_entity();
        REQUIRE(eid == 1);

        // Add component
        REQUIRE(entity_manager.add_component(std::make_unique<test_component>(), eid));

        // Check component added
        REQUIRE(entity_manager.get_component<test_component>(core::component_type::body, eid) != nullptr);

        // Remove component
        REQUIRE(entity_manager.remove_component(core::component_type::body, eid));

        // Check component removed
        REQUIRE_FALSE(entity_manager.get_component<test_component>(core::component_type::body, eid) != nullptr);
    }
}
