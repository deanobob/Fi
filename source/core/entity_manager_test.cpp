/// @file entity_manager_test.cpp

#include "catch2/catch.hpp"
#include "body_component.hpp"
#include "component.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "message_entity_added.hpp"
#include "message_entity_removed.hpp"
#include "subscriber.hpp"

/// @brief A test subscriber
class test_listener
    : public core::subscriber
{
    public:
    /// @brief Constructor - subscribes to messages from entity_manager
    /// @param message_bus The message bus
    test_listener(core::message_bus& message_bus)
        : m_message_bus(message_bus)
    {
        m_message_bus.subscribe(
            this,
            {
                messages::message_entity_added::TYPE,
                messages::message_entity_removed::TYPE
            }
        );
    }

    /// @brief Destructor
    virtual ~test_listener()
    {
        m_message_bus.unsubscribe(this);
    }

    /// @param p_message The message
    void on_publish(core::message* p_message)
    {
        if (p_message->get_type() == messages::message_entity_added::TYPE)
        {
            m_num_added++;
        }
        else if (p_message->get_type() == messages::message_entity_removed::TYPE)
        {
            m_num_removed++;
        }
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
    /// @brief Reference to the message_bus
    core::message_bus& m_message_bus;
    /// @brief Number of added messages
    uint32_t m_num_added{0};
    /// @brief Number of removed messages
    uint32_t m_num_removed{0};
};

TEST_CASE("core/entity_manager.hpp Entity Manager", "[entity_manager]")
{
    core::message_bus message_bus{};
    core::entity_manager entity_manager{message_bus};

    SECTION("1 Put entity")
    {
        test_listener listener(message_bus);

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
        test_listener listener(message_bus);

        auto entity = std::make_unique<core::entity>();
        auto id = entity->get_id();
        entity_manager.put(std::move(entity));
        REQUIRE(entity_manager.remove(id));
        REQUIRE_FALSE(entity_manager.remove(id));
        REQUIRE(listener.num_added() == 1);
        REQUIRE(listener.num_removed() == 1);
    }
}
