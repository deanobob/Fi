/// @file draw_manager.hpp
/// @brief The draw_manager class

#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "gametime.hpp"
#include "message_bus.hpp"
#include "render_controller.hpp"
#include "render_event_listener.hpp"
#include "text_alignment.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Manages rendering the game
    class draw_manager
        : public render::render_event_listener
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Pointer to the message bus
        /// @param p_render_controller Pointer to the render_controller
        draw_manager(core::message_bus* p_message_bus, render::render_controller* p_render_controller);
        /// @brief Destructor
        virtual ~draw_manager();

        /// @brief Creates the game window and loads resources
        /// @param window_properties The properties that define how the window will be configured on creation
        /// @return True if initialised successfully
        bool initialise(const render::window_properties& window_properties);

        /// @brief Processes window events etc.
        void process_events();

        /// @brief Define the transform position, scale, and rotation for the upcoming renderables
        /// @param viewport The viewport of the transform
        /// @param scale The scale to apply to all renderables
        /// @param rotation The rotation to apply to all renderables
        void begin(const utilities::rectangle& viewport,
                   const utilities::vector2& scale = utilities::vector2::ONE,
                   const float rotation = 0.0f);

        /// @brief Clear the draw buffers
        void clear();

        /// @brief Draw line to the display from p1 to p2
        /// @param p1 The start point
        /// @param p2 The end point
        /// @param color The colour of the line. Defaults to white.
        /// @param thickness The line thickness
        void draw_line(
            const utilities::vector2& p1,
            const utilities::vector2& p2,
            const utilities::color& color = utilities::colors::white,
            float thickness = 1);

        /// @brief Draw circle to the display
        /// @param cx The centre X coordinate
        /// @param cy The centre Y coordinate
        /// @param radius The radius of the circle
        /// @param color The colour of the circle. Defaults to white.
        /// @param thickness The circle line thickness
        void draw_circle(
            const float cx,
            const float cy,
            const float radius,
            const utilities::color& color = utilities::colors::white,
            float thickness = 1);


        /// @brief Draw rectangle
        /// @param rect The rectangle to draw
        /// @param color The line colour
        void draw_rectangle(const utilities::rectangle& rect, const utilities::color& color);

        /// @brief Draw filled rectangle
        /// @param rect The rectangle to draw
        /// @param color The fill colour
        void draw_filled_rectangle(const utilities::rectangle& rect, const utilities::color& color);

        /// @brief Draws text to the display at the given position
        /// @param res_id The text resource id
        /// @param text The text to draw
        /// @param position The position of the text
        /// @param color The colour of the text
        /// @param text_alignment The text justification
        void draw_text(
            const render::resource_id& res_id,
            const std::string& text,
            const utilities::vector2& position,
            const utilities::color& color,
            const ui::text_alignment text_alignment);

        /// @brief Draws a sprite to the display at the given position
        /// @param res_id The bitmap resource id
        /// @param position The position of the text
        void draw_bitmap(const render::resource_id& res_id, const utilities::vector2& position);

        /// @brief Pops the last transform
        void end();

        /// @brief Flips the buffers
        void flip();

        /// @brief Destroy the window and tidy up
        void shutdown();

        void on_display_resize(int width, int height) override;

        void on_display_close() override;

        void on_display_gained_focus() override;

        void on_display_lost_focus() override;

        private:
        /// @brief Pointer to the message bus
        core::message_bus* mp_message_bus {nullptr};
        /// @brief Pointer to render controller
        render::render_controller* mp_render_controller {nullptr};
        /// @brief Queue of all transforms applied to the draw manager
        std::list<render::transform> m_transforms {};
    };
} /// namespace core

#endif /// DRAW_MANAGER_HPP
