/// @file message_new_game.hpp
/// @brief Message that notifies subscribers that all entities have been cleared

#ifndef MESSAGE_NEW_GAME_HPP
#define MESSAGE_NEW_GAME_HPP

#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that starts a new game
    class message_new_game
        : public core::message
    {
        public:
        /// @brief Default destructor
        virtual ~message_new_game() = default;

        /// @brief The message type
        static constexpr auto TYPE { "NEW_GAME" };

        const std::string get_type() const override { return TYPE; };
    };
} /// namespace messages

#endif /// MESSAGE_NEW_GAME_HPP
