/// @file mouse.hpp

#ifndef MOUSE_HPP
#define MOUSE_HPP

/// @namespace services namespace
namespace services
{
    /// @brief Enum class containing definitions for all mouse buttons that the game will process
    enum class mouse_button : unsigned int
    {
        unknown = 0,
        left,
        right
    };
} /// namespace services

#endif /// MOUSE_HPP
