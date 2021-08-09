/// @file render_component.hpp
/// @brief The render component

#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The render component
    class render_component
        : public component
    {
        public:
        /// @brief Get the render component type
        /// @return The render component type
        component_type get_type() const override
        {
            return component_type::render;
        }
    };
} /// namespace core

#endif /// RENDER_COMPONENT_HPP
