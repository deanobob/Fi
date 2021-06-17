/// @file message_entity_added.hpp
/// @brief Message that informs the application an entity has been added

#ifndef MESSAGE_ENTITY_ADDED_HPP
#define MESSAGE_ENTITY_ADDED_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that causes the application to resume if paused
    class message_entity_added : public messaging::message
    {
        public:
        /// @brief The message type
        static constexpr auto TYPE { "ENTITY_ADDED" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_ENTITY_ADDED_HPP
