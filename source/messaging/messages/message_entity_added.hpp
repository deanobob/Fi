/// @file message_entity_added.hpp
/// @brief Message that informs the application an entity has been added

#ifndef MESSAGE_ENTITY_ADDED_HPP
#define MESSAGE_ENTITY_ADDED_HPP

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that informs subscribers that an entity has been added
    class message_entity_added : public messaging::message
    {
        public:
        /// @brief Constructor
        /// @param p_entity Reference to the entity that was added
        message_entity_added(core::entity* p_entity)
            : mp_entity{p_entity}
        {

        }

        /// @brief The message type
        static constexpr auto TYPE { "ENTITY_ADDED" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the entity pointer
        /// @return The entity
        core::entity* get_entity()
        {
            return mp_entity;
        }

        private:
        /// @brief Reference to the newly added entity
        core::entity* mp_entity{nullptr};
    };
} /// namespace messages

#endif /// MESSAGE_ENTITY_ADDED_HPP
