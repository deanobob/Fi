/// @file event_args.hpp
/// @brief Base class for event arguments

#ifndef EVENT_ARGS_HPP
#define EVENT_ARGS_HPP

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Base class for event arguments
    class event_args
    {
        public:
        /// @brief Default empty event args
        static const event_args NONE;

        /// @brief Default constructor
        event_args() = default;
        /// @brief Default destructor
        virtual ~event_args() = default;
    };
} /// namespace messaging

#endif /// EVENT_ARGS_HPP
