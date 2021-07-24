/// @file simulation_view.hpp

#ifndef SIMULATION_VIEW_HPP
#define SIMULATION_VIEW_HPP

#include "camera.hpp"
#include "node.hpp"
#include "subscriber.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief A UI element that renders a simulation camera elements
    class simulation_view
        : public node
        , public core::subscriber
    {
        public:
        /// @brief Construct a new simulation view object
        simulation_view(core::message_bus* p_message_bus, core::camera* p_camera);
        /// @brief Destroy the simulation view object
        virtual ~simulation_view() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void mouse_axis_changed(int position_x, int position_y, int position_z) override;

        void on_publish(core::message* p_message) override;

        private:
        /// @brief The simulation camera that this simulation view renders
        core::camera* mp_camera{nullptr};
    };
} /// namespace ui

#endif /// SIMULATION_VIEW_HPP
