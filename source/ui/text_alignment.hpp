/// @file text_alignment.hpp

#ifndef TEXT_ALIGNMENT_HPP
#define TEXT_ALIGNMENT_HPP

/// @namespace ui namespace
namespace ui
{
    /// @brief The alignment of the text
    enum class text_alignment : unsigned int
    {
        /// @brief Align the left side of the text to the X position
        left = 0,
        /// @brief Align the center of the text to the X position
        centre = 1,
        /// @brief Align the right side of the text to the X position
        right = 2
    };
} /// namespace ui

#endif /// TEXT_ALIGNMENT_HPP
