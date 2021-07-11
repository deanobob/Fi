/// @file ui_service.hpp
/// @brief Manages the UI state

#ifndef UI_SERVICE_HPP
#define UI_SERVICE_HPP

#include "gametime.hpp"
#include "service.hpp"

/// @namespace ui namespace
namespace ui
{
    /// @brief Manages the game UI state
    class ui_service
        : public core::service
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus Reference to the game message bus
        ui_service(core::message_bus* p_message_bus);
        /// @brief Destructor
        virtual ~ui_service();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager) override;

        void shutdown() override;

        void on_publish(core::message* p_message) override {};
    };
} /// namespace ui

#endif /// UI_SERVICE_HPP
