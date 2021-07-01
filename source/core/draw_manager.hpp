/// @file draw_manager.hpp
/// @brief The draw_manager base class

#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "renderer.hpp"

/// @namespace core namespace
namespace core
{
    /// Forward declarations
    class game;

    /// @brief Manages rendering the game
    class draw_manager
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        draw_manager(game* p_game);
        /// @brief Default destructor
        virtual ~draw_manager() = default;

        /// @brief Creates the game window and loads resources
        /// @return True if initialised successfully
        bool initialise();
        /// @brief Update entity positions
        /// @param delta The remaining duration of this frame
        void draw(double delta);
        /// @brief Destroy the window and tidy up
        void shutdown();

        private:
        /// @brief Reference to renderer system
        framework::renderer* mp_renderer {nullptr};
    };
} /// namespace core

#endif /// DRAW_MANAGER_HPP
