/// @file camera.hpp
/// @brief A game camera used to manage what the UI is rendering in a window.


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "rectangle.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The camera class
    class camera
    {
        public:
        /// @brief Construct a new camera object
        /// @param viewport The camera viewport
        camera(const utilities::rectangle& viewport);

        private:
        /// @brief The camera viewport
        utilities::rectangle m_viewport{};
    };
} /// namespace core

#endif /// CAMERA_HPP
