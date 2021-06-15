/// @file component.hpp
/// @brief Base class for components

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The base component class
    class component
    {
        public:
        /// @brief Default destructor
        virtual ~component() = default;

        /// @brief Get the component type
        /// @return The component type
        virtual component_type get_type() const = 0;
    };
} /// namespace core

#endif /// COMPONENT_HPP
