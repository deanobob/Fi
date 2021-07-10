/// @file key.hpp

#ifndef KEY_HPP
#define KEY_HPP

/// @namespace input namespace
namespace input
{
    /// @brief Enum class containing definitions for all keyboard keys that the game will process
    enum class key : unsigned int
    {
        unknown = 0,
        left,
        right,
        up,
        down,
        r,
        space,
        escape
    };
} /// input services

#endif /// KEY_HPP
