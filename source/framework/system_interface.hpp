/// @file system_interface.hpp

#ifndef SYSTEM_INTERFACE_HPP
#define SYSTEM_INTERFACE_HPP

#include <memory>
#include "allegro_input.hpp"
#include "allegro_renderer.hpp"
#include "input.hpp"
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

        /// @brief Get the input system
        /// @return Reference to the input instance
        input* get_input()
        {
            if (!m_input)
            {
                m_input = std::make_unique<allegro_input>();
            }
            return m_input.get();
        }

        private:
        /// @brief The renderer instance
        std::unique_ptr<renderer> m_renderer {nullptr};
        /// @brief The input instance
        std::unique_ptr<input> m_input {nullptr};
    };
}

#endif /// SYSTEM_INTERFACE_HPP
