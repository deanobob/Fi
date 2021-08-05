/// @file camera_controller.hpp
/// @brief Manages the cameras within the game

#ifndef CAMERA_CONTROLLER_HPP
#define CAMERA_CONTROLLER_HPP

#include <map>
#include <memory>
#include "camera.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The camera controller class
    class camera_controller
    {
        public:
        /// @brief Adds a new camera
        /// @param p_camera The camera
        /// @param tag A tag string identifying the camera
        void add_camera(std::unique_ptr<camera> p_camera, const std::string& tag = "");

        /// @brief Get a camera by id
        /// @param camera_id The camera ID
        /// @return Pointer to the camera or nullptr if not found
        core::camera* get_camera_by_id(const uint32_t camera_id) const;

        /// @brief Get a camera by tag
        /// @param camera_tag The camera tag
        /// @return Pointer to the camera or nullptr if not found
        core::camera* get_camera_by_tag(const std::string& camera_tag) const;

        /// @brief Get cameras
        /// @return All the cameras
        const std::list<core::camera*>& get_cameras() const;

        private:
        /// @brief List containing pointer to all cameras
        std::list<core::camera*> m_cameras{};
        /// @brief The simulation cameras
        std::map<const uint32_t, std::unique_ptr<core::camera> > m_cameras_by_id{};
        /// @brief Lookup map of cameras stored by tag name
        std::map<const std::string, core::camera*> m_cameras_by_tag{};

    };
} /// namespace core

#endif /// CAMERA_CONTROLLER_HPP
