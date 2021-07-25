/// @file alignment.hpp

#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

/// @brief ui namespace
namespace ui
{
    /// @brief The horizontal alignment enum type
    /// @details Determines how a UI element is aligned horizontally
    enum class horizontal_alignment : unsigned int
    {
        left = 0,
        right = 1,
        centre = 2
    };

    /// @brief The vertical alignment enum type
    /// @details Determines how a UI element is aligned vertically
    enum class vertical_alignment : unsigned int
    {
        top = 0,
        bottom = 1,
        centre = 2
    };
} /// namespace ui

#endif /// ALIGNMENT_HPP
