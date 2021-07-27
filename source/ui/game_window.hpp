/// @file game_window.hpp

#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include "camera.hpp"
#include "root.hpp"
#include "simulation_view.hpp"
#include "subscriber.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic game_window UI element
    /// @details Contains and manages child elements
    class game_window
        : public root
        , public core::subscriber
    {
        public:
        /// @brief Construct a new game window object
        /// @param p_message_bus The message bus
        /// @param p_camera The game camera
        game_window(core::message_bus* p_message_bus, core::camera* p_camera);
        /// @brief Destroy the game window object
        virtual ~game_window() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void on_publish(core::message* p_message) override;

        private:
        /// @brief The message bus
        core::message_bus* mp_message_bus{nullptr};

        /// @brief The simulation view
        ui::simulation_view* mp_simulation_view{nullptr};
    };
} /// namespace ui

#endif /// GAME_WINDOW_HPP
