/// @file camera.hpp
/// @brief A game camera used to manage what the UI is rendering in a window.


#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <list>
#include <memory>
#include <stdlib.h>
#include <tuple>
#include "color.hpp"
#include "gametime.hpp"
#include "rectangle.hpp"
#include "render_controller.hpp"
#include "text_alignment.hpp"

/// @namespace core namespace
namespace core
{
    enum class renderable_type : uint32_t
    {
        line,
        rectangle,
        circle,
        arc,
        sprite,
        text
    };

    class renderable
    {
        public:
        virtual ~renderable()
        {

        }

        virtual renderable_type get_type() const = 0;
    };

    class renderable_line
        : public renderable
    {
        public:
        const float m_x1;
        const float m_y1;
        const float m_x2;
        const float m_y2;
        const int m_thickness;

        renderable_line(float x1, float y1, float x2, float y2, int thickness)
            : m_x1{x1}
            , m_y1{y1}
            , m_x2{x2}
            , m_y2{y2}
            , m_thickness{thickness}
        {}

        virtual ~renderable_line()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::line;
        }
    };

    class renderable_rectangle
        : public renderable
    {
        public:
        const float m_x;
        const float m_y;
        const float m_width;
        const float m_height;
        const float m_rotation;
        const int m_thickness;

        renderable_rectangle(float x, float y, float width, float height, float rotation, int thickness)
            : m_x{x}
            , m_y{y}
            , m_width{width}
            , m_height{height}
            , m_rotation{rotation}
            , m_thickness{thickness}
        {}

        virtual ~renderable_rectangle()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::rectangle;
        }
    };

    class renderable_sprite
        : public renderable
    {
        public:
        const float m_x;
        const float m_y;
        const render::resource_id m_sprite_res_id;

        renderable_sprite(
            float x,
            float y,
            const render::resource_id sprite_res_id)
            : m_x{x}
            , m_y{y}
            , m_sprite_res_id{sprite_res_id}
        {

        }

        virtual ~renderable_sprite()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::sprite;
        }
    };

    class renderable_text
        : public renderable
    {
        public:
        const float m_x;
        const float m_y;
        const render::resource_id m_font_res_id;
        const std::string m_text;
        const utilities::color m_color;
        const ui::text_alignment m_alignment;

        renderable_text(
            float x,
            float y,
            const render::resource_id font_res_id,
            const std::string& text,
            const utilities::color& color = {255, 255, 255},
            const ui::text_alignment alignment = ui::text_alignment::left)
            : m_x{x}
            , m_y{y}
            , m_font_res_id{font_res_id}
            , m_text{text}
            , m_color{color}
            , m_alignment{alignment}
        {

        }

        virtual ~renderable_text()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::text;
        }
    };

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
        void add_renderable(std::unique_ptr<renderable> renderable);

        /// @brief Get renderables
        /// @return The renderable list
        const std::list<std::unique_ptr<renderable> >& get_renderables() const;

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
        std::list<std::unique_ptr<renderable> > m_renderables{};
    };
} /// namespace core

#endif /// CAMERA_HPP
