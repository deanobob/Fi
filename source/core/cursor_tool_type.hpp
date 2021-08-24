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
        none,
        track_0_deg,
        track_90_deg,
        track_180_deg,
        track_270_deg,
    };
} /// namespace core

#endif /// COMPONENT_TYPE_HPP