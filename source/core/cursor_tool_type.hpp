/// @file cursor_tool_type.hpp
/// @brief Defines the cursor tool types enum

#ifndef CURSOR_TOOL_TYPE_HPP
#define CURSOR_TOOL_TYPE_HPP

/// @namespace core namespace
namespace core
{
    /// @enum cursor_tool_type The cursor tool type enum
    /// @brief The tool types that can be selected for use with the cursor
    enum class cursor_tool_type : unsigned int
    {
        none,
        track_0_deg,
        track_45_deg,
        track_90_deg,
        track_135_deg,
        grass,
    };
} /// namespace core

#endif /// COMPONENT_TYPE_HPP
