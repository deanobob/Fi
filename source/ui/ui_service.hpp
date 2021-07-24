/// @file ui_service.hpp
/// @brief Manages the UI state

#ifndef UI_SERVICE_HPP
#define UI_SERVICE_HPP

#include <memory>
#include "gametime.hpp"
#include "input_controller.hpp"
#include "root.hpp"
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
        /// @param p_input_controller The input controller
        ui_service(core::message_bus* p_message_bus, input::input_controller* p_input_controller);
        /// @brief Destructor
        virtual ~ui_service();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(core::draw_manager* p_draw_manager) override;

        void shutdown() override;

        void on_publish(core::message* p_message) override;

        private:
        /// @brief Reference to input system
        input::input_controller* mp_input_controller{nullptr};
        /// @brief The root UI node
        std::unique_ptr<ui::root> mp_root_node{nullptr};
    };
} /// namespace ui

#endif /// UI_SERVICE_HPP
