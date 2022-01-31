/// @file message_entity_added.hpp
/// @brief Message that notifies subscribers that an entity has been added
/// 
/// @copyright Copyright (c) 2021
/// 

#ifndef MESSAGE_ENTITY_ADDED_HPP
#define MESSAGE_ENTITY_ADDED_HPP

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies subscribers that an entity has been added
    class message_entity_added
        : public core::message
    {
        public:
        /// @brief Construct a new message entity added object
        /// @param p_entity The added entity
        message_entity_added(core::entity* p_entity)
            : mp_entity{p_entity}
        {}

        /// @brief Destroy the message entity added object
        virtual ~message_entity_added() = default;

        /// @brief The message type
        static constexpr auto TYPE { "ENTITY_ADDED" };
        
        const std::string get_type() const override { return TYPE; };

        /// @brief Get entity
        /// @return Pointer to the new entity
        core::entity* get_entity() const
        {
            return mp_entity;
        }

        private:
        /// @brief The added entity
        core::entity* mp_entity{nullptr};
    };
} /// namespace messages

#endif /// MESSAGE_ENTITY_ADDED_HPP
