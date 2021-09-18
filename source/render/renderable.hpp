/// @file renderable.hpp
/// @brief Classes that define renderable simulation elements

#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <list>
#include <memory>
#include <stdlib.h>
#include <tuple>
#include "color.hpp"
#include "gametime.hpp"
#include "rectangle.hpp"
#include "render_controller.hpp"
#include "text_alignment.hpp"

/// @namespace render namespace
namespace render
{
    /// @brief Defines the renderable types
    enum class renderable_type : uint32_t
    {
        line,
        rectangle,
        circle,
        arc,
        sprite,
        text
    };

    /// @brief The base renderable class
    class renderable
    {
        public:
        /// @brief Destroy the renderable object
        virtual ~renderable()
        {

        }

        /// @brief Get the renderable type
        /// @return renderable_type The renderable type
        virtual renderable_type get_type() const = 0;
    };

    /// @brief A renderable line defined by two points
    class renderable_line
        : public renderable
    {
        public:
        /// @brief Point 1 X coordinate
        const float m_x1;
        /// @brief Point 1 Y coordinate
        const float m_y1;
        /// @brief Point 2 X coordinate
        const float m_x2;
        /// @brief Point 2 Y coordinate
        const float m_y2;
        /// @brief The colour of the line
        const utilities::color m_color;
        /// @brief The line thickness
        const float m_thickness;

        /// @brief Construct a new renderable line object
        ///
        /// @param x1 The point 1 X coordinate
        /// @param y1 The point 1 Y coordinate
        /// @param x2 The point 2 X coordinate
        /// @param y2 The point 2 Y coordinate
        /// @param color The colour of the line
        /// @param thickness The line thickness
        renderable_line(float x1, float y1, float x2, float y2, const utilities::color& color, float thickness)
            : m_x1{x1}
            , m_y1{y1}
            , m_x2{x2}
            , m_y2{y2}
            , m_color{color}
            , m_thickness{thickness}
        {

        }

        /// @brief Destroy the renderable line object
        virtual ~renderable_line()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::line;
        }
    };

    /// @brief A renderable circle defined by a centre point and a radius
    class renderable_circle
        : public renderable
    {
        public:
        /// @brief The centre X position
        const float m_cx;
        /// @brief The centre Y position
        const float m_cy;
        /// @brief The radius of the circle
        const float m_radius;
        /// @brief The colour of the circle line
        const utilities::color m_color;
        /// @brief The thickness of the line
        const float m_thickness;

        /// @brief Construct a new renderable circle object
        /// @param cx The centre X position
        /// @param cy The centre Y position
        /// @param radius The radius of the circle
        /// @param color The colour of the circle line
        /// @param thickness The thickness of the line
        renderable_circle(float cx, float cy, float radius, const utilities::color& color, float thickness)
            : m_cx{cx}
            , m_cy{cy}
            , m_radius{radius}
            , m_color{color}
            , m_thickness{thickness}
        {

        }

        /// @brief Destroy the renderable circle object
        virtual ~renderable_circle()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::circle;
        }
    };

    /// @brief A renderable circle defined by a top-left point and a width / height
    class renderable_rectangle
        : public renderable
    {
        public:
        /// @brief The top left point X coordiate
        const float m_x;
        /// @brief The top left point Y coordinate
        const float m_y;
        /// @brief The rectangle width
        const float m_width;
        /// @brief The rectangle height
        const float m_height;
        /// @brief The rectangle rotation
        const float m_rotation;
        /// @brief The colour of the rectangle line
        const utilities::color m_color;
        /// @brief The line thickness
        const float m_thickness;

        /// @brief Construct a new renderable rectangle object
        /// @param x The top left point X coordiate
        /// @param y The top left point Y coordiate
        /// @param width The rectangle width
        /// @param height The rectangle height
        /// @param rotation The rectangle rotation
        /// @param color The colour of the rectangle line
        /// @param thickness The line thickness
        renderable_rectangle(
            float x,
            float y,
            float width,
            float height,
            float rotation,
            const utilities::color& color,
            float thickness)
            : m_x{x}
            , m_y{y}
            , m_width{width}
            , m_height{height}
            , m_rotation{rotation}
            , m_color{color}
            , m_thickness{thickness}
        {

        }

        /// @brief Destroy the renderable rectangle object
        virtual ~renderable_rectangle()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::rectangle;
        }
    };

    /// @brief A renderable sprite at a given position
    class renderable_sprite
        : public renderable
    {
        public:
        /// @brief The top left X coordinate
        const float m_x;
        /// @brief The top left Y coordinate
        const float m_y;
        /// @brief The sprite resource id
        const render::resource_id m_sprite_res_id;

        /// @brief Construct a new renderable sprite object
        /// @param x The top left X coordinate
        /// @param y The top left Y coordinate
        /// @param sprite_res_id The sprite resource id
        renderable_sprite(
            float x,
            float y,
            const render::resource_id sprite_res_id)
            : m_x{x}
            , m_y{y}
            , m_sprite_res_id{sprite_res_id}
        {

        }

        /// @brief Destroy the renderable sprite object
        virtual ~renderable_sprite()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::sprite;
        }
    };

    /// @brief The renderable text
    class renderable_text
        : public renderable
    {
        public:
        /// @brief The X coordinate
        const float m_x;
        /// @brief The Y coordinate
        const float m_y;
        /// @brief The font resource id
        const render::resource_id m_font_res_id;
        /// @brief The text to render
        const std::string m_text;
        /// @brief The colour of the text
        const utilities::color m_color;
        /// @brief The alignment of the text
        const ui::text_alignment m_alignment;

        /// @brief Construct a new renderable text object
        /// @param x The X coordinate
        /// @param y The Y coordinate
        /// @param font_res_id The font resource id
        /// @param text The text to render
        /// @param color The colour of the text
        /// @param alignment The alignment of the text
        renderable_text(
            float x,
            float y,
            const render::resource_id font_res_id,
            const std::string& text,
            const utilities::color& color = utilities::colors::white,
            const ui::text_alignment alignment = ui::text_alignment::left)
            : m_x{x}
            , m_y{y}
            , m_font_res_id{font_res_id}
            , m_text{text}
            , m_color{color}
            , m_alignment{alignment}
        {

        }

        /// @brief Destroy the renderable text object
        virtual ~renderable_text()
        {

        }

        renderable_type get_type() const override
        {
            return renderable_type::text;
        }
    };
}

#endif /// RENDERABLE_HPP
