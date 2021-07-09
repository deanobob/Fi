/// @file draw_manager.hpp
/// @brief The draw_manager base class

#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "gametime.hpp"
#include "renderer.hpp"
#include "renderer_event_listener.hpp"

/// @namespace core namespace
namespace core
{
    /// Forward declarations
    class game;

    /// @brief Manages rendering the game
    class draw_manager
        : public framework::renderer_event_listener
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        draw_manager(game* p_game);
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
        /// @brief Pointer to renderer system
        framework::renderer* mp_renderer{nullptr};

        /// @brief Pointer to game
        game* mp_game{nullptr};
    };
} /// namespace core

#endif /// DRAW_MANAGER_HPP
