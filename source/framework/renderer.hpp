/// @file renderer.hpp

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>
#include "color.hpp"
#include "rectangle.hpp"
#include "vector2.hpp"

/// @namespace framework namespace
namespace framework
{
    /// @brief The window properties struct
    /// @details Defines the properties that are used when generating a renderer window
    struct window_properties
    {
        /// @brief Undefined window position
        static constexpr auto WINDOW_POSITION_UNDEFINED{0};
        /// @brief The default window width
        static constexpr auto DEFAULT_WINDOW_WIDTH{1024};
        /// @brief The default window height
        static constexpr auto DEFAULT_WINDOW_HEIGHT{720};
        /// @brief The default number of msaa samples
        static constexpr auto DEFAULT_MSAA_SAMPLES{8};

        /// @brief The window title
        std::string title{""};
        /// @brief The x position of the window
        int x{WINDOW_POSITION_UNDEFINED};
        /// @brief The y position of the window
        int y{WINDOW_POSITION_UNDEFINED};
        /// @brief The width of the window
        uint32_t width{DEFAULT_WINDOW_WIDTH};
        /// @brief The height of the window
        uint32_t height{DEFAULT_WINDOW_HEIGHT};
        /// @brief Flag defining whether the window should display in fullscreen mode
        bool fullscreen{false};
        /// @brief Flag defining whether the window is resizeable
        bool resizeable{true};
        /// @brief Flag defining if vsync is enabled
        bool vsync{true};
        /// @brief Flag defining if msaa is enabled
        bool msaa_enabled{true};
        /// @brief The number of msaa samples
        uint8_t msaa_samples{DEFAULT_MSAA_SAMPLES};
    };

    /// @brief Defines the renderer window location scale and rotation.
    struct transform
    {
        /// @brief The viewport boundaries
        utilities::rectangle viewport{};
        /// @brief The transform scale
        utilities::vector2 scale{utilities::vector2::ONE};
        /// @brief The transform rotation in radians
        float rotation{0.0f};
    };

    /// @brief The renderer class
    class renderer
    {
        public:
        /// @brief flags - converted from SDL as required
        static constexpr auto FLAGS_WINDOW_OPENGL = 2;

        /// @brief Initialise the renderer
        /// @return True on success, false if failed to intialise
        virtual bool initialise() = 0;

        /// @brief Create an application window
        /// @param properties The window properties
        /// @return True on success, false if failure to create window
        virtual bool create_window(const window_properties& properties) = 0;

        /// @brief Set the clear colour
        /// @param color The colour that is used to clear the backbuffer
        virtual void set_clear_color(const utilities::color& color) = 0;

        /// @brief Clear the backbuffer
        virtual void clear() = 0;

        /// @brief Set the viewport transform
        /// @param transform The transform object
        virtual void set_transform(const transform& transform) = 0;

        /// @brief Load a bitmap into the cache (if not already loaded), create a sub-bitmap at the position
        /// and size given, then return a unique bitmap ID
        /// @param filename The bitmap filename
        /// @param position The source bitmap offset to begin the sub-bitmap
        /// @param size The size of the sub-bitmap
        /// @param bitmap_id The unique bitmap ID
        /// @return True if bitmap successfully generated, else False
        virtual bool load_bitmap(const std::string& filename,
                                 const utilities::vector2& position,
                                 const utilities::vector2& size,
                                 uint32_t& bitmap_id) = 0;

        /// @brief Load a TTF font into the cache and return a unique font ID
        /// @param filename The font filename
        /// @param font_size The font size
        /// @param flags Flags specific to the renderer
        /// @param font_id The unique font ID
        /// @return True if font successfully loaded, else False
        virtual bool load_font(const std::string& filename,
                               uint32_t font_size,
                               uint32_t flags,
                               uint32_t& font_id) = 0;

        /// @brief Render a bitmap
        /// @param bitmap_id The bitmap ID
        /// @param position The position to render the bitmap
        /// @param flags Flags specific to the renderer
        virtual void render_bitmap(uint32_t bitmap_id,
                                   const utilities::vector2& position,
                                   uint32_t flags) = 0;

        /// @brief Render a filled rectangle
        /// @param rect The rectangle to draw
        /// @param color The rectangle fill colour
        virtual void render_fill_rect(const utilities::rectangle& rect,
                                      const utilities::color& color) = 0;

        /// @brief Render a line
        /// @param x1 The first point X position
        /// @param y1 The first point Y position
        /// @param x2 The second point X position
        /// @param y2 The second point Y position
        /// @param color The line colour
        virtual void render_draw_line(float x1,
                                      float y1,
                                      float x2,
                                      float y2,
                                      const utilities::color& color) = 0;

        /// @brief Render text at given position
        /// @param font_id The ID of the font
        /// @param text The text
        /// @param x The x position of the text
        /// @param y The y position of the text
        /// @param color The colour of the text
        /// @param flags Flags specific to the renderer
        virtual void render_text(uint32_t font_id,
                                 const std::string& text,
                                 float x,
                                 float y,
                                 const utilities::color& color,
                                 uint32_t flags) = 0;

        /// @brief Flip the draw buffer
        virtual void flip() = 0;

        /// @brief Destroy the window
        virtual void destroy_window() = 0;

        /// @brief Terminates all renderer functions
        virtual void shutdown() = 0;
    };

} /// namespace framework

#endif /// RENDERER_HPP
