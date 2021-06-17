/// @file component_type.hpp
/// @brief Defines the component types enum

#ifndef COMPONENT_TYPE_HPP
#define COMPONENT_TYPE_HPP

#include <stdlib.h>
#include <type_traits>

/// @namespace core namespace
namespace core
{
    /// @enum component_type The component type enum
    /// @brief Contains bitwise operation compatible types for components
    enum class component_type : uint32_t
    {
        none = 0 << 0,
        body = 1 << 0,
        render = 1 << 1,
        placeholder = 1 << 2,
        // TODO: define more
    };

    /// @brief Defines an OR operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator | (component_type lhs, component_type rhs)
    {
        using T = std::underlying_type_t <component_type>;
        return static_cast<component_type>(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    /// @brief Defines an OR assignment operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator |= (component_type& lhs, component_type rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    /// @brief Defines an AND operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator & (component_type lhs, component_type rhs)
    {
        using T = std::underlying_type_t <component_type>;
        return static_cast<component_type>(static_cast<T>(lhs) & static_cast<T>(rhs));
    }

    /// @brief Defines an AND assignment operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator &= (component_type& lhs, component_type rhs)
    {
        lhs = lhs & rhs;
        return lhs;
    }

    /// @brief Defines an XOR operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator ^ (component_type lhs, component_type rhs)
    {
        using T = std::underlying_type_t <component_type>;
        return static_cast<component_type>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
    }

    /// @brief Defines an XOR assignment operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator ^= (component_type& lhs, component_type rhs)
    {
        lhs = lhs ^ rhs;
        return lhs;
    }

    /// @brief Defines an NOT operator for component type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline component_type operator ~(component_type& lhs)// operator ~ (component_type lhs, component_type rhs)
    {
        using T = std::underlying_type_t <component_type>;
        return static_cast<component_type>(~static_cast<T>(lhs));
    }
} /// namespace core

#endif /// COMPONENT_TYPE_HPP
