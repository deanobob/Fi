/// @file key.hpp

#ifndef KEY_HPP
#define KEY_HPP

/// @namespace services namespace
namespace services
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
} /// namespace services

#endif /// KEY_HPP
