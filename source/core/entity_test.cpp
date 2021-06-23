/// @file entity_test.cpp

#include "catch2/catch.hpp"
#include "component.hpp"
#include "entity.hpp"

/// @brief A test component
class test_component : public core::component
{
    public:
    /// @brief Constructor
    /// @param type Optional component type override, defaults to body
    test_component(core::component_type type = core::component_type::body)
        : m_type{type}
    {
    }

    /// @brief Get the component type
    /// @return The component type
    core::component_type get_type() const override
    {
        return m_type;
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
    /// @brief The component type
    const core::component_type m_type;
    /// @brief The test counter
    uint32_t m_test_counter{0};
};

/// @brief A test entity
class test_entity : public core::entity
{
    public:
    /// @brief The total number of times update is called
    uint32_t m_total_updates{0};

    /// @brief Test override function that counts the number of times it is called
    /// @param gametime The gametime
    void on_update(utilities::gametime& gametime) override
    {
        m_total_updates++;
    }
};

TEST_CASE("core/entity.hpp Entity", "[entity]")
{
    SECTION("1 Create entity")
    {
        // Create entity with empty tag
        auto entity1{core::entity()};
        REQUIRE(entity1.get_tag().empty());
        // Create entity with tag, ensure the ID incremented
        auto entity2{core::entity("dave")};
        REQUIRE(entity2.get_id() == entity1.get_id() + 1);
        REQUIRE(entity2.get_tag() == "dave");
    }

    SECTION("2 Add component")
    {
        // Create entity
        auto entity{core::entity()};
        // Add component
        REQUIRE(entity.add_component(std::make_unique<test_component>()));
        // Check component added
        REQUIRE(entity.get_component<test_component>(core::component_type::body) != nullptr);
        // Check get non-existent component fails
        REQUIRE_FALSE(entity.get_component<test_component>(core::component_type::render) != nullptr);
    }

    SECTION("3 Add components")
    {
        // Create entity
        auto entity{core::entity()};
        // Add body component
        REQUIRE(entity.add_component(std::make_unique<test_component>(core::component_type::body)));
        // Check body component added
        REQUIRE(entity.get_component<test_component>(core::component_type::body) != nullptr);
        // Check get render component fails
        REQUIRE_FALSE(entity.get_component<test_component>(core::component_type::render) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == core::component_type::body);
        // Add render component
        REQUIRE(entity.add_component(std::make_unique<test_component>(core::component_type::render)));
        // Check render component added
        REQUIRE(entity.get_component<test_component>(core::component_type::render) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == (core::component_type::body | core::component_type::render));
    }

    SECTION("4 Get component allows modification of component")
    {
        // Create entity
        auto entity{core::entity()};

        // Add component
        REQUIRE(entity.add_component(std::make_unique<test_component>()));

        // Check test component returned and counter increments
        auto component = entity.get_component<test_component>(core::component_type::body);
        REQUIRE(component != nullptr);
        REQUIRE(component->get_count() == 0);
        component->increment_counter();
        REQUIRE(component->get_count() == 1);

        // Check test component returned with updated counter and continues to increment
        component = entity.get_component<test_component>(core::component_type::body);
        REQUIRE(component != nullptr);
        REQUIRE(component->get_count() == 1);
        component->increment_counter();
        REQUIRE(component->get_count() == 2);
    }

    SECTION("5 Remove component")
    {
        // Create entity
        auto entity{core::entity()};
        // Add component
        REQUIRE(entity.add_component(std::make_unique<test_component>()));
        // Check component added
        REQUIRE(entity.get_component<test_component>(core::component_type::body) != nullptr);
        // Remove component
        REQUIRE(entity.remove_component(core::component_type::body));
        // Check component removed
        REQUIRE_FALSE(entity.get_component<test_component>(core::component_type::body) != nullptr);
    }

    SECTION("6 Remove components")
    {
        // Create entity
        auto entity{core::entity()};
        // Add body component
        REQUIRE(entity.add_component(std::make_unique<test_component>(core::component_type::body)));
        // Check body component added
        REQUIRE(entity.get_component<test_component>(core::component_type::body) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == core::component_type::body);
        // Add render component
        REQUIRE(entity.add_component(std::make_unique<test_component>(core::component_type::render)));
        // Check render component added
        REQUIRE(entity.get_component<test_component>(core::component_type::render) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == (core::component_type::body | core::component_type::render));

        // Remove component
        REQUIRE(entity.remove_component(core::component_type::body));
        // Check component removed
        REQUIRE_FALSE(entity.get_component<test_component>(core::component_type::body) != nullptr);
        // Check render component available
        REQUIRE(entity.get_component<test_component>(core::component_type::render) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == core::component_type::render);

        // Remove render component
        REQUIRE(entity.remove_component(core::component_type::render));
        // Check render component removed
        REQUIRE_FALSE(entity.get_component<test_component>(core::component_type::render) != nullptr);
        // Check component mask is correct
        REQUIRE(entity.get_component_mask() == core::component_type::none);
    }

    SECTION("7 Update entity")
    {
        // Create entity with empty tag
        auto entity1{test_entity()};
        auto gametime{utilities::gametime()};
        REQUIRE(entity1.m_total_updates == 0);
        entity1.update(gametime);
        REQUIRE(entity1.m_total_updates == 0);
        entity1.update_on_tick();
        entity1.update(gametime);
        REQUIRE(entity1.m_total_updates == 1);
        entity1.update(gametime);
        REQUIRE(entity1.m_total_updates == 2);
    }
}
