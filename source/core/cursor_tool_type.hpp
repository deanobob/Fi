/// @file cursor_tool_tyle.hpp
/// @brief Defines the cursor tool types enum

#ifndef CURSOR_TOOL_TYPE_HPP
#define CURSOR_TOOL_TYPE_HPP

/// @namespace core namespace
namespace core
{
    /// @enum component_type The component type enum
    /// @brief The tool types that can be selected for use with the cursor
    enum class cursor_tool_type : unsigned int
    {
        ZERO_DEG_STRAIGHT_TRACK,
        NINETY_DEG_STRAIGHT_TRACK,
    };
} /// namespace core

#endif /// COMPONENT_TYPE_HPP