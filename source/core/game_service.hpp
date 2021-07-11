/// @file game_service.hpp
/// @brief The game_service base class

#ifndef GAME_SERVICE_HPP
#define GAME_SERVICE_HPP

#include "gametime.hpp"
#include "service.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Manages the game simulation e.g. loading, saving, etc.
    class game_service
        : public core::service
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        game_service(message_bus* p_message_bus);
        /// @brief Destructor
        virtual ~game_service();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager) override;

        void shutdown() override;
        
        void on_publish(core::message* p_message) override;
    };
} /// namespace core

#endif /// GAME_SERVICE_HPP
