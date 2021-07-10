/// @file game.hpp
/// @brief The base game class that a game extends

#ifndef GAME_HPP
#define GAME_HPP

#include <atomic>
#include <map>
#include <memory>
#include "draw_manager.hpp"
#include "entity_manager.hpp"
#include "gametime.hpp"
#include "message_bus.hpp"
#include "service.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The base game class
    class game
        : public subscriber
    {
        public:
        /// @brief Message bus shared across all services
        message_bus m_message_bus{};

        /// @brief Constructor
        game();
        /// @brief Default destructor
        virtual ~game();

        /// @brief The root of the game
        /// @details Initialises the game and loops until an exit message is received
        void run();
        /// @brief Request the game to exit
        void exit();

        /// @brief Handles events from message_bus the game has subscribed to
        /// @param p_message The message
        void on_publish(message* p_message) override;

        /// @brief Get the framework system interface
        /// @return A pointer to the framework system interface
        framework::system_interface* get_system_interface();

        /// @brief Get the service of the given type, cast to the template type
        /// @note Defined in header due to non-specialized template
        /// @param type The service type
        /// @return The service pointer cast to template type T or nullptr
        template <typename T>
        T* get_service(service_type type)
        {
            const auto& service_iter = m_services.find(type);
            if (service_iter == m_services.end())
            {
                // Component of given type doesn't exist
                return nullptr;
            }

            return dynamic_cast<T*>(service_iter->second.get());
        }

        private:
        /// @brief Flag indicating whether to exit the game
        std::atomic<bool> m_exit_game{false};
        /// @brief Flag recording the game paused state
        std::atomic<bool> m_paused{false};
        /// @brief Records the elapsed and total time the game has been running
        utilities::gametime m_gametime{};
        /// @brief Container for services
        std::map<service_type, std::unique_ptr<service> > m_services{};
        /// @brief Framework system interface
        framework::system_interface m_system_interface{};
        /// @brief The entity manager;
        entity_manager m_entity_manager;
        /// @brief The draw manager
        draw_manager m_draw_manager;

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
