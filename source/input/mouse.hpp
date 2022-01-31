/// @file mouse.hpp

#ifndef MOUSE_HPP
#define MOUSE_HPP

/// @namespace input namespace
namespace input
{
    /// @brief Enum class containing definitions for all mouse buttons that the game will process
    enum class mouse_button : unsigned int
    {
        unknown = 0,
        left,
        right
    };
} /// namespace input

#endif /// MOUSE_HPP
