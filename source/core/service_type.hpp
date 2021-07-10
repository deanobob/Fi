/// @file service_type.hpp
/// @brief Defines the service types enum

#ifndef SERVICE_TYPE_HPP
#define SERVICE_TYPE_HPP

#include <stdlib.h>
#include <type_traits>

/// @namespace core namespace
namespace core
{
    /// @enum service_type The service type enum
    /// @brief Contains bitwise operation compatible types for services
    enum class service_type : unsigned int
    {
        none = 0 << 0,
        console = 1 << 0,
        input_manager = 1 << 1,
        render_service = 1 << 2,
        // TODO: define more
    };

    /// @brief Defines an OR operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator | (service_type lhs, service_type rhs)
    {
        using T = std::underlying_type_t <service_type>;
        return static_cast<service_type>(static_cast<T>(lhs) | static_cast<T>(rhs));
    }

    /// @brief Defines an OR assignment operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator |= (service_type& lhs, service_type rhs)
    {
        lhs = lhs | rhs;
        return lhs;
    }

    /// @brief Defines an AND operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator & (service_type lhs, service_type rhs)
    {
        using T = std::underlying_type_t <service_type>;
        return static_cast<service_type>(static_cast<T>(lhs) & static_cast<T>(rhs));
    }

    /// @brief Defines an AND assignment operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator &= (service_type& lhs, service_type rhs)
    {
        lhs = lhs & rhs;
        return lhs;
    }

    /// @brief Defines an XOR operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator ^ (service_type lhs, service_type rhs)
    {
        using T = std::underlying_type_t <service_type>;
        return static_cast<service_type>(static_cast<T>(lhs) ^ static_cast<T>(rhs));
    }

    /// @brief Defines an XOR assignment operator for service type enum
    /// @param lhs The left hand side
    /// @param rhs The right hand side
    /// @return The result of the operation
    inline service_type operator ^= (service_type& lhs, service_type rhs)
    {
        lhs = lhs ^ rhs;
        return lhs;
    }

    /// @brief Defines an NOT operator for service type enum
    /// @param lhs The left hand side
    /// @return The result of the operation
    inline service_type operator ~(service_type& lhs)
    {
        using T = std::underlying_type_t <service_type>;
        return static_cast<service_type>(~static_cast<T>(lhs));
    }
} /// namespace core

#endif /// SERVICE_TYPE_HPP
