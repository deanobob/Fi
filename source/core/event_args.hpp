/// @file event_args.hpp
/// @brief Event args base class

#ifndef EVENT_ARGS_HPP
#define EVENT_ARGS_HPP

#include <stdint.h>

/// @namespace core namespace
namespace core
{
    /// @brief The event args base class
    class event_args
    {
        public:
        /// @brief Destroy the event args object
        virtual ~event_args() {};
    };
} /// namespace core

#endif /// EVENT_ARGS_HPP