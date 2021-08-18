/// @file render_component.hpp
/// @brief The render component

#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief alias for render types
    using render_type = std::string;

    /// @brief The render component
    class render_component
        : public component
    {
        public:
        /// @brief Construct a new render component object
        /// @param render_type The render type
        render_component(const render_type& render_type = "")
            : m_render_type{render_type}
        {
            
        }

        /// @brief Get the render component type
        /// @return The render component type
        component_type get_type() const override
        {
            return component_type::render;
        }

        const render_type& get_render_type() const
        {
            return m_render_type;
        }

        private:
        /// @brief The type of rendering required for this entity
        const render_type m_render_type;
    };
} /// namespace core

#endif /// RENDER_COMPONENT_HPP
