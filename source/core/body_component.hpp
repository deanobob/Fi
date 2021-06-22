/// @file body_component.hpp
/// @brief The body component

#ifndef BODY_COMPONENT_HPP
#define BODY_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The body component
    class body_component : public component
    {
        public:
        /// @brief Get the body component type
        /// @return The body component type
        component_type get_type() const override
        {
            return component_type::body;
        }
    };
} /// namespace core

#endif /// BODY_COMPONENT_HPP
