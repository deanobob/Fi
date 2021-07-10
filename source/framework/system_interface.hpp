/// @file system_interface.hpp

#ifndef SYSTEM_INTERFACE_HPP
#define SYSTEM_INTERFACE_HPP

#include <memory>
#include "allegro_input_controller.hpp"
#include "allegro_renderer.hpp"
#include "input_controller.hpp"
#include "renderer.hpp"

/// @namespace framework namespace
namespace framework
{
    /// @brief Class that provides access to framework systems
    class system_interface
    {
        public:
        /// @brief Get the renderer system
        /// @return Reference to the renderer instance
        renderer* get_renderer()
        {
            if (!m_renderer)
            {
                m_renderer = std::make_unique<allegro_renderer>();
            }
            return m_renderer.get();
        }

        /// @brief Get the input controller
        /// @return Reference to the input controller
        input_controller* get_input_controller()
        {
            if (!m_input)
            {
                m_input = std::make_unique<allegro_input_controller>();
            }
            return m_input.get();
        }

        private:
        /// @brief The renderer instance
        std::unique_ptr<renderer> m_renderer {nullptr};
        /// @brief The input controller instance
        std::unique_ptr<input_controller> m_input {nullptr};
    };
}

#endif /// SYSTEM_INTERFACE_HPP
