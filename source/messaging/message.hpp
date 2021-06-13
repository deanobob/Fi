/// @file message.hpp
/// @brief Base class for messages

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

/// @namespace messaging namespace
namespace messaging
{
    /// @brief Base class for event arguments
    class message
    {
        public:
        /// @brief Default constructor
        message() = default;
        /// @brief Default destructor
        virtual ~message() = default;

        /// @brief Gets the message type
        /// @return The message type
        virtual const std::string get_type() const = 0;
    };
} /// namespace messaging

#endif /// MESSAGE_HPP
