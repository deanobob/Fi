/// @file message_entity_removed.hpp
/// @brief Message that informs the application an entity is being removed

#ifndef MESSAGE_ENTITY_REMOVED
#define MESSAGE_ENTITY_REMOVED

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that informs subscribers a message is being removed
    class message_entity_removed : public messaging::message
    {
        public:
        /// @brief Constructor
        /// @param p_entity Reference to the entity that is being removed
        message_entity_removed(core::entity* p_entity) :
            mp_entity{p_entity}
        {

        }

        /// @brief The message type
        static constexpr auto TYPE { "ENTITY_REMOVED" };

        const std::string get_type() const override { return TYPE; };

        private:
        /// @brief Reference to the removed entity
        const core::entity* mp_entity;
    };
} /// namespace messages

#endif /// MESSAGE_ENTITY_REMOVED
