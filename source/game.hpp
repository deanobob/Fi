/// @file game.hpp
/// @brief The base game class that a game extends

#ifndef GAME_HPP
#define GAME_HPP

#include <atomic>
#include "publisher.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The base game class
    class game : public messaging::subscriber
    {
        public:
        /// @brief The exit game event type name
        static constexpr auto EVENT_EXIT_GAME = "EXIT_GAME";

        /// @brief Constructor
        game();
        /// @brief Default destructor
        virtual ~game();

        /// @brief The root of the game
        /// @details Initialises the game and loops until an exit message is received
        void run();
        /// @brief Request the game to exit
        void exit();

        /// @brief Handles events from publishers the game has subscribed to
        /// @param p_message The message
        void on_publish(const messaging::message* p_message) override;

        private:
        /// @brief Flag indicating whether to exit the game
        std::atomic<bool> m_exit_game{false};
        /// @brief Publisher that notifies subscribers the game is exiting
        messaging::publisher m_game_status_messager;

        /// @brief Initialise the game
        bool initialise();

        /// @brief Shutdown the game
        void shutdown();
    };
} /// namespace core

#endif /// GAME_HPP
