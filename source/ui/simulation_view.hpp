/// @file simulation_view.hpp

#ifndef SIMULATION_VIEW_HPP
#define SIMULATION_VIEW_HPP

#include "camera.hpp"
#include "message_bus.hpp"
#include "node.hpp"
#include "subscriber.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief A UI element that renders a simulation camera elements
    class simulation_view
        : public node
    {
        public:
        /// @brief Construct a new simulation view object
        /// @param p_message_bus The message bus
        /// @param p_camera The simulation view camera
        simulation_view(core::message_bus* p_message_bus, core::camera* p_camera);
        /// @brief Destroy the simulation view object
        virtual ~simulation_view() = default;

        protected:
        void on_initialise() override;

        void on_load(core::resource_manager* p_resource_manager) override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void on_focus_lost() override;

        void mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y) override;

        void mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y) override;

        void mouse_axis_changed(int position_x, int position_y, int position_z) override;

        private:
        /// @brief The message bus
        core::message_bus* mp_message_bus{nullptr};

        /// @brief The simulation camera that this simulation view renders
        core::camera* mp_camera{nullptr};

        /// @brief Flag indicating if the right mouse is pressed
        bool m_is_right_button_pressed{false};

        /// @brief Last mouse position
        utilities::vector2 m_last_mouse_position{};
    };
} /// namespace ui

#endif /// SIMULATION_VIEW_HPP
