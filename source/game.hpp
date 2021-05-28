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
        game() = default;
        virtual ~game() = default;
        
        void initialise();
        void run();
    };
} /// namespace core

#endif /// GAME_HPP