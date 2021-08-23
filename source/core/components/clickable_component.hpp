/// @file clickable_component.hpp
/// @brief The clickable component

#ifndef CLICKABLE_COMPONENT_HPP
#define CLICKABLE_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The clickable component
    class clickable_component
        : public component
    {
        public:
        /// @brief Get the clickable component type
        /// @return The clickable component type
        component_type get_type() const override
        {
            return component_type::clickable;
        }
    };
} /// namespace core

#endif /// CLICKABLE_COMPONENT_HPP
