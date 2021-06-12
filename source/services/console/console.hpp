/// @file console.hpp
/// @brief The console base class

#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "gametime.hpp"
#include "command.hpp"
#include "server.hpp"
#include "service.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Base class for services
    class console : public core::service, public utilities::server
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

        protected:
        /// @brief Converts TCP messages into commands and pushes them to the command buffer
        /// @param message The received message
        void on_receive(const std::string& message);

        private:
        /// @brief Buffer that contains the available commands
        std::map<const std::string, std::shared_ptr<services::command> > m_commands;
        /// @brief Message buffer mutex
        /// @details Synchronises the command buffer access across the read thread and the game thread
        std::mutex m_command_buffer_mutex{};
        /// @brief Buffer that contains commands generated by the console, awaiting despatch on next update
        std::vector<std::tuple<command*, const std::vector<std::string> > > m_command_buffer;

        /// @brief Adds a command to the available command map
        /// @param command The command to add to the map
        void add_command(std::shared_ptr<services::command> command);
    };
} /// namespace services

#endif /// CONSOLE_HPP
