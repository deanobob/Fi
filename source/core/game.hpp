/// @file game.hpp
/// @brief The base game class that a game extends

#ifndef GAME_HPP
#define GAME_HPP

#include <atomic>
#include <memory>
#include <vector>
#include "gametime.hpp"
#include "publisher.hpp"
#include "service.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The base game class
    class game : public messaging::subscriber
    {
        public:
        /// @brief Publisher that notifies subscribers the game is exiting
        messaging::publisher m_game_status_messager{};

        /// @brief Constructor
        game();
        /// @brief Default destructor
        virtual ~game() = default;

        /// @brief The root of the game
        /// @details Initialises the game and loops until an exit message is received
        void run();
        /// @brief Request the game to exit
        void exit();

        /// @brief Handles events from publishers the game has subscribed to
        /// @param p_message The message
        void on_publish(const messaging::message* p_message) override;

        /// @brief Get the framework system interface
        /// @return A reference to the framework system interface
        framework::system_interface* get_system_interface();

        private:
        /// @brief Flag indicating whether to exit the game
        std::atomic<bool> m_exit_game{false};
        /// @brief Flag recording the game paused state
        std::atomic<bool> m_paused{false};
        /// @brief Records the elapsed and total time the game has been running
        utilities::gametime m_gametime{};
        /// @brief Container for services
        std::vector<std::unique_ptr<service> > m_services;
        /// @brief Framework system interface
        framework::system_interface m_system_interface{};

        /// @brief Initialise the game
        bool initialise();
        /// @brief Called on every tick to update services
        void update();
        /// @brief Shutdown the game
        void shutdown();

        /// @brief Add service to game
        /// @param service The service to add
        void add_service(std::unique_ptr<service> service);
    };
} /// namespace core

#endif /// GAME_HPP
