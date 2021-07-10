/// @file message_entity_removed.hpp
/// @brief Message that notifies subscribers that an entity has been removed

#ifndef MESSAGE_ENTITY_REMOVED_HPP
#define MESSAGE_ENTITY_REMOVED_HPP

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies subscribers that an entity has been removed
    class message_entity_removed
        : public core::message
    {
        public:
        /// @brief Constructor
        message_entity_removed(core::entity* p_entity)
            : mp_entity{p_entity}
        {}

        /// @brief Default destructor
        virtual ~message_entity_removed() = default;

        /// @brief The message type
        static constexpr auto TYPE { "ENTITY_REMOVED" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get entity
        /// @return Pointer to the removed entity
        core::entity* get_entity() const
        {
            return mp_entity;
        }

        private:
        /// @brief The newly removed entity
        core::entity* mp_entity{nullptr};
    };
} /// namespace messages

#endif /// MESSAGE_ENTITY_REMOVED_HPP
