/// @file camera.hpp
/// @brief A game camera used to manage what the UI is rendering in a window.


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <list>
#include <tuple>
#include "rectangle.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Renderable type - temporary until a real renderable is defined
    using renderable = std::tuple<float, float>;

    /// @brief The camera class
    class camera
    {
        public:
        /// @brief Construct a new camera object
        /// @param viewport The camera viewport
        camera(const utilities::rectangle& viewport);

        /// @brief Get the viewport
        /// @return The viewport
        const utilities::rectangle& get_viewport() const;

        /// @brief Add renderable to renderables list
        /// @param renderable The renderable structure
        void add_renderable(const renderable& renderable);

        /// @brief Get renderables
        /// @return The renderable list
        const std::list<renderable>& get_renderables() const;

        /// @brief Clear renderables
        void clear();

        private:
        /// @brief The camera viewport
        utilities::rectangle m_viewport{};
        /// @brief List of renderables within the camera viewport
        /// @details On draw the game simulation will fill this structure with the renderable items within the camera
        /// viewport, which is then retrieved by the gameview that is attached to the camera.
        std::list<renderable> m_renderables{}; 
    };
} /// namespace core

#endif /// CAMERA_HPP
