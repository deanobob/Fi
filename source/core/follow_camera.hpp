/// @file follow_camera.hpp
/// @brief Like a normal camera but follows an entity


#ifndef FOLLOW_CAMERA_HPP
#define FOLLOW_CAMERA_HPP

#include "camera.hpp"
#include "entity.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The follow camera class
    class follow_camera
        : public camera
    {
        public:
        /// @brief Construct a new follow_camera object
        /// @param viewport The follow_camera viewport
        follow_camera(entity* p_entity, const utilities::rectangle& viewport = utilities::rectangle::EMPTY);

        /// @brief Called on every update tick allowing the follow_camera to update
        void update(const utilities::gametime& p_gametime) override;

        private:
        /// @brief The entity to follow
        core::entity* mp_entity{nullptr};
    };
} /// namespace core

#endif /// FOLLOW_CAMERA_HPP
