/// @file console.hpp
/// @brief The console base class

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <atomic>
#include <thread>
#include "service.hpp"
#include "gametime.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Base class for services
    class console : public core::service
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        console(core::game* p_game);

        /// @brief Initialises the console reader
        /// @return True if initialised successfully
        bool initialise();
        /// @brief Called on every tick allowing console input to be processed
        void update(utilities::gametime& gametime) override;
        /// @brief Shutsdown the service
        void shutdown() override;

        private:
        /// @brief Flag indicating if the thread is running
        std::atomic<bool> m_running{true};
        /// @brief The thread that reads input from stdin
        std::thread m_read_thread{};

        /// @brief Continually reads input from stdin until the application shuts down
        void read_input();
    };
} /// namespace services

#endif /// CONSOLE_HPP
