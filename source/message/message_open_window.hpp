/// @file message_open_window.hpp
/// @brief Message that requests a window is opened

#ifndef MESSAGE_OPEN_WINDOW_HPP
#define MESSAGE_OPEN_WINDOW_HPP

#include "camera.hpp"
#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies a new game has been created
    class message_open_window
        : public core::message
    {
        public:
        /// @brief Construct a message open window object
        /// @param p_camera The game camera
        message_open_window(core::camera* p_camera)
            : mp_camera{p_camera}
        {
            assert(mp_camera != nullptr);
        }

        /// @brief Destroy the message open window object
        virtual ~message_open_window() = default;

        /// @brief The message type
        static constexpr auto TYPE { "OPEN_WINDOW" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the simulation camera
        /// @return Pointer to the camera
        core::camera* get_camera() const
        {
            return mp_camera;
        }

        private:
        /// @brief The game main camera
        core::camera* mp_camera{nullptr};
    };
} /// namespace messages

#endif /// MESSAGE_OPEN_WINDOW_HPP
