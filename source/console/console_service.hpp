/// @file console_service.hpp
/// @brief The console service class

#ifndef CONSOLE_SERVICE_HPP
#define CONSOLE_SERVICE_HPP

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "command.hpp"
#include "entity_manager.hpp"
#include "gametime.hpp"
#include "server.hpp"
#include "service.hpp"

/// @namespace console namespace
namespace console
{
    /// @brief Service that provides a console interface to the game
    class console_service
        : public core::service
        , public utilities::server
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Pointer to the game message bus
        /// @param p_entity_manager Pointer to the entity manager
        console_service(core::message_bus* p_message_bus, core::entity_manager* p_entity_manager);
        /// @brief Destructor
        virtual ~console_service() = default;

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager) override;

        void shutdown() override;
        
        void on_publish(core::message* p_message) override {};

        /// @brief Returns false for pausable check, ensuring service runs when game is paused
        /// @return True if pauseable, else false
        bool pauseable() const override;

        protected:
        /// @brief Converts TCP messages into commands and pushes them to the command buffer
        /// @param message The received message
        void on_receive(const std::string& message);

        private:
        /// @brief Buffer that contains the available commands
        std::map<const std::string, std::shared_ptr<command> > m_commands;
        /// @brief Message buffer mutex
        /// @details Synchronises the command buffer access across the read thread and the game thread
        std::mutex m_command_buffer_mutex{};
        /// @brief Buffer that contains commands generated by the console, awaiting despatch on next update
        std::vector<std::tuple<command*, const std::vector<std::string> > > m_command_buffer;

        /// @brief Adds a command to the available command map
        /// @param command The command to add to the map
        void add_command(std::shared_ptr<command> command);
    };
} /// namespace console

#endif /// CONSOLE_HPP
