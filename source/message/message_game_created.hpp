/// @file message_game_created.hpp
/// @brief Message that notifies subscribers that a game has been created

#ifndef MESSAGE_GAME_CREATED_HPP
#define MESSAGE_GAME_CREATED_HPP

#include "camera.hpp"
#include "entity.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies a new game has been created
    class message_game_created
        : public core::message
    {
        public:
        /// @brief Construct a message new game object
        message_game_created(core::camera* p_camera)
            : mp_camera{p_camera}
        {
            assert(mp_camera != nullptr);
        }

        /// @brief Destroy the message new game object
        virtual ~message_game_created() = default;

        /// @brief The message type
        static constexpr auto TYPE { "GAME_CREATED" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the main simulation camera
        /// @return Pointer to the main camera
        core::camera* get_camera() const
        {
            return mp_camera;
        }

        private:
        /// @brief The game main camera
        core::camera* mp_camera{nullptr};
    };
} /// namespace messages

#endif /// MESSAGE_GAME_CREATED_HPP
