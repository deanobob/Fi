/// @file component_type.hpp
/// @brief Defines the component types enum

#ifndef COMPONENT_TYPE_HPP
#define COMPONENT_TYPE_HPP

#include <stdlib.h>

/// @namespace core namespace
namespace core
{
    enum class component_type : uint32_t
    {
        body = 0,
        render = 1,
        // TODO: define more
    };
} /// namespace core

#endif /// COMPONENT_TYPE_HPP
