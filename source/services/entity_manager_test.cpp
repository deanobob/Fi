/// @file entity_manager_test.cpp

#include "catch2/catch.hpp"
#include "body_component.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "entity_manager_listener.hpp"

/// @brief A test subscriber
class test_listener
    : public services::entity_manager_listener
{
    public:
    /// @brief Constructor - subscribes to messages from entity_manager
    /// @param p_entity_manager The entity manager
    test_listener(services::entity_manager* p_entity_manager)
        : mp_entity_manager{p_entity_manager}
    {
        mp_entity_manager->add_listener(this);
    }

    /// @brief Destructor - unsubscribes from entity_manager
    virtual ~test_listener()
    {
        mp_entity_manager->remove_listener(this);
    }

    void on_entity_added(core::entity* p_entity) override
    {
        m_num_added++;
    }

    void on_entity_removed(core::entity* p_entity) override
    {
        m_num_removed++;
    }

    /// @brief Get the number of added messages
    /// @return The number of added messages
    uint32_t num_added() const
    {
        return m_num_added;
    }

    /// @brief Get the number of removed messages
    /// @return The number of removed messages
    uint32_t num_removed() const
    {
        return m_num_removed;
    }

    private:
    /// @brief Reference to the entity manager
    services::entity_manager* mp_entity_manager{nullptr};
    /// @brief Number of added messages
    uint32_t m_num_added{0};
    /// @brief Number of removed messages
    uint32_t m_num_removed{0};
};

TEST_CASE("core/entity_manager.hpp Entity Manager", "[entity_manager]")
{
    services::entity_manager entity_manager{nullptr};

    SECTION("1 Put entity")
    {
        test_listener listener(&entity_manager);

        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.get(id) != nullptr);
        REQUIRE(entity_manager.get(id + 1) == nullptr);
        REQUIRE(listener.num_added() == 1);
        REQUIRE(listener.num_removed() == 0);
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
        test_listener listener(&entity_manager);

        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.remove(id));
        REQUIRE_FALSE(entity_manager.remove(id));
        REQUIRE(listener.num_added() == 1);
        REQUIRE(listener.num_removed() == 1);
    }
}
