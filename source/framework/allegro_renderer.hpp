/// @file allegro_renderer.hpp

#ifndef ALLEGRO_RENDERER_HPP
#define ALLEGRO_RENDERER_HPP

#include <list>
#include <map>
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "renderer.hpp"

namespace framework
{
    /// @brief Implementation of renderer framework interface using liballegro
    class allegro_renderer: public renderer
    {
        public:
        /// @brief Constructor
        /// @param p_event_queue The allegro event queue
        allegro_renderer(ALLEGRO_EVENT_QUEUE* p_event_queue);

        bool initialise() override;

        bool create_window(const window_properties& properties) override;

        void set_clear_color(const utilities::color& color) override;

        void clear() override;

        void set_transform(const transform& transform) override;

        bool load_bitmap(const std::string& filename,
                         const utilities::vector2& position,
                         const utilities::vector2& size,
                         uint32_t& bitmapId) override;

        bool load_font(const std::string& filename,
                       uint32_t font_size,
                       uint32_t flags,
                       uint32_t& fontId) override;

        void render_bitmap(uint32_t bitmapId,
                           const utilities::vector2& position,
                           uint32_t flags) override;

        void render_fill_rect(const utilities::rectangle& rect,
                              const utilities::color& color) override;

        void render_draw_line(float x1,
                              float y1,
                              float x2,
                              float y2,
                              const utilities::color& color) override;

        void render_text(const uint32_t font_id,
                         const std::string& text,
                         float x,
                         float y,
                         const utilities::color& color,
                         uint32_t flags) override;

        void flip() override;

        void destroy_window() override;

        void shutdown() override;

        private:
        /// @brief The allegro event queue
        ALLEGRO_EVENT_QUEUE* mp_event_queue{nullptr};
        /// @brief Teh allegro display instance
        ALLEGRO_DISPLAY* mp_display{nullptr};
        /// @brief The bitmap instance that the window draws
        ALLEGRO_BITMAP* mp_target{nullptr};
        /// @brief The backbuffer clear colour
        ALLEGRO_COLOR m_clear_color{};
        /// @brief Stores the next unique ID for a font UID
        uint32_t m_next_font_id{1};
        /// @brief Stores the next unique ID for a sprite UID
        uint32_t m_next_sprite_id{1};
        /// @brief Font name and size mapped to font filename
        std::map<std::string, uint32_t> m_font_ids;
        /// @brief Cache of allegro fonts
        std::map<uint32_t, ALLEGRO_FONT*> m_font_cache;
        /// @brief Parent bitmaps mapped to the source filename
        std::map<std::string, ALLEGRO_BITMAP*> m_bitmap_cache;
        /// @brief Contains sub-bitmap sprites sharing memory of parent bitmaps stored in bitmap_cache
        std::map<uint32_t, ALLEGRO_BITMAP*> m_sprite_cache;

        /// @brief Get the bitmap by UID
        /// @param bitmap_id The bitmap unique ID
        /// @return The allegro bitmap or nullptr if not found
        ALLEGRO_BITMAP* get_bitmap(uint32_t bitmap_id) const;

        /// @brief Get the location where the assets are stored
        /// @return The assets path
        const std::string get_assets_path() const;
    };

} /// namespace framework

#endif /// ALLEGRO_RENDERER_HPP
