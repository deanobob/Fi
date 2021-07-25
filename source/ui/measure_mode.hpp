/// @file measure_mode.hpp

#ifndef MEASURE_MODE_HPP
#define MEASURE_MODE_HPP

/// @brief ui namespace
namespace ui
{
    /// @brief The measure mode enum type
    /// @details Determines how a UI element is measured
    enum class measure_mode
    {
        fixed,
        inflate,
        wrap
    };
} /// namespace ui

#endif /// UI_MEASURE_MODE_HPP
