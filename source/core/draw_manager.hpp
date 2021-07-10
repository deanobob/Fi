/// @file draw_manager.hpp
/// @brief The draw_manager base class

#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "gametime.hpp"
#include "message_bus.hpp"
#include "render_controller.hpp"
#include "render_event_listener.hpp"

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
        /// @return True if initialised successfully
        bool initialise();

        /// @brief Processes window events etc.
        void process_events();

        /// @brief Update entity positions and render game
        /// @param delta The remaining duration of this frame
        void draw(double delta);

        /// @brief Destroy the window and tidy up
        void shutdown();

        void on_display_close() override;

        void on_display_gained_focus() override;

        void on_display_lost_focus() override;

        private:
        /// @brief Pointer to the message bus
        core::message_bus* mp_message_bus{nullptr};
        /// @brief Pointer to render controller
        render::render_controller* mp_render_controller{nullptr};

    };
} /// namespace core

#endif /// DRAW_MANAGER_HPP
