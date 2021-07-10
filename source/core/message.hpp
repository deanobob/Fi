/// @file message.hpp
/// @brief Base class for messages

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

/// @namespace core namespace
namespace core
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
} /// namespace core

#endif /// MESSAGE_HPP
