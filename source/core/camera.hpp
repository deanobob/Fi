/// @file camera.hpp
/// @brief A game camera used to manage what the UI is rendering in a window.

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <vector>
#include <memory>
#include <stdlib.h>
#include <tuple>
#include "color.hpp"
#include "gametime.hpp"
#include "rectangle.hpp"
#include "renderable.hpp"
#include "render_controller.hpp"
#include "text_alignment.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The camera class
    class camera
    {
        public:
        /// @brief Construct a new camera object
        /// @param position The camera position
        camera(const utilities::vector2& position = utilities::vector2::ZERO);

        /// @brief Get the camera unique identifier
        /// @return The unique camera identifier
        uint32_t get_id() const;

        /// @brief Set the position of the camera
        /// @param position The new position of the camera
        void set_position(const utilities::vector2& position);

        /// @brief Set the dimensions of the camera
        /// @param size The dimensions of the camera
        void set_dimensions(const utilities::vector2& size);

        /// @brief Move the camera
        /// @param offset The value added to the current position to move the camera
        void move(const utilities::vector2& offset);

        /// @brief Get the viewport
        /// @return The viewport
        const utilities::rectangle& get_viewport() const;

        /// @brief Add renderable to renderables list
        /// @param renderable The renderable structure
        void add_renderable(std::unique_ptr<render::renderable> renderable);

        /// @brief Get renderables
        /// @return The renderable list
        const std::vector<std::unique_ptr<render::renderable> >& get_renderables() const;

        /// @brief Called on every update tick allowing the camera to update
        /// @param gametime The gametime maintaining instance
        virtual void update(const utilities::gametime& gametime);

        /// @brief Clear renderables
        void clear();

        private:
        /// @brief Stores the next unique ID for a camera
        static uint32_t m_next_id;

        /// @brief The unique ID of the camera
        const unsigned int m_id;

        /// @brief The camera viewport
        utilities::rectangle m_viewport{};

        /// @brief List of renderables within the camera viewport
        /// @details On draw the game simulation will fill this structure with the renderable items within the camera
        /// viewport, which is then retrieved by the gameview that is attached to the camera.
        std::vector<std::unique_ptr<render::renderable> > m_renderables{};
    };
} /// namespace core

#endif /// CAMERA_HPP
