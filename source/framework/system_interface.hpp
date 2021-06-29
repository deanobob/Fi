/// @file system_interface.hpp

#ifndef SYSTEM_INTERFACE_HPP
#define SYSTEM_INTERFACE_HPP

#include <memory>
#include "renderer.hpp"
#include "allegro_renderer.hpp"

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

        private:
        /// @brief The renderer instance
        std::unique_ptr<renderer> m_renderer {nullptr};
    };
}

#endif /// SYSTEM_INTERFACE_HPP
