/// @file message_entities_cleared.hpp
/// @brief Message that notifies subscribers that all entities have been cleared

#ifndef MESSAGE_ENTITIES_CLEARED_HPP
#define MESSAGE_ENTITIES_CLEARED_HPP

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies subscribers that all entities have been cleared
    class message_entities_cleared
        : public core::message
    {
        public:
        /// @brief Default destructor
        virtual ~message_entities_cleared() = default;

        /// @brief The message type
        static constexpr auto TYPE { "ENTITIES_CLEARED" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_ENTITIES_CLEARED_HPP
