/// @file game.hpp
/// @brief The base game class that a game extends

#ifndef GAME_HPP
#define GAME_HPP

/// @namespace core namespace
namespace core
{
    /// @brief The base game class
    class game
    {
        public:
        /// @brief Default constructor
        game() = default;
        /// @brief Default destructor
        virtual ~game() = default;

        /// @brief The root of the game
        /// @details Initialises the game and loops until an exit message is received
        void run();
        /// @brief Request the game to exit
        void exit();

        private:
        /// @brief Flag indicating whether to exit the game
        bool exit_game{false};

        /// @brief Initialise the game
        bool initialise();

        /// @brief Shutdown the game
        void shutdown();
    };
} /// namespace core

#endif /// GAME_HPP
