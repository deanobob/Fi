/// @file strings.hpp
/// @brief Contains string utilities

#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>
#include <vector>

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that contains string utilities
    class strings
    {
        public:
        /// @brief Tokenise a string by the given delimiter
        /// @param str The string
        /// @param delimiter The delimiter character - defaults to space
        /// @return A vector containing the tokens
        static const std::vector<std::string> tokenise(const std::string& str, const char delimiter = ' ');

        private:
        /// @brief Default constructor
        strings() = default;
        /// @brief Default destructor
        ~strings() = default;
    };
} /// namespace utilities

#endif /// STRINGS_HPP
