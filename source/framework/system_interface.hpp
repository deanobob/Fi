/// @file system_interface.hpp

#ifndef SYSTEM_INTERFACE_HPP
#define SYSTEM_INTERFACE_HPP

#include <memory>
#include "allegro_input_controller.hpp"
#include "allegro_render_controller.hpp"
#include "input_controller.hpp"
#include "render_controller.hpp"

/// @namespace framework namespace
namespace framework
{
    /// @brief Class that provides access to framework systems
    class system_interface
    {
        public:
        /// @brief Get the renderer system
        /// @return Pointer to the render controller
        render::render_controller* get_render_controller()
        {
            if (!m_render_controller)
            {
                m_render_controller = std::make_unique<render::allegro_render_controller>();
            }
            return m_render_controller.get();
        }

        /// @brief Get the input system
        /// @return Pointer to the input controller
        input::input_controller* get_input_controller()
        {
            if (!m_input_controller)
            {
                m_input_controller = std::make_unique<input::allegro_input_controller>();
            }
            return m_input_controller.get();
        }

        private:
        /// @brief The render controller instance
        std::unique_ptr<render::render_controller> m_render_controller {nullptr};
        /// @brief The input controller instance
        std::unique_ptr<input::input_controller> m_input_controller {nullptr};
    };
}

#endif /// SYSTEM_INTERFACE_HPP
