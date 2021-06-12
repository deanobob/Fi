/// @file strings.cpp

#include <algorithm>
#include <sstream>
#include "strings.hpp"

namespace utilities
{
    const std::vector<std::string> strings::tokenise(const std::string& str, const char delimiter)
    {
        std::vector<std::string> result{};

        std::stringstream tmp_ss{str};
        std::string token{};

        while (std::getline(tmp_ss, token, delimiter))
        {
            result.push_back(token);
        }

        return result;
    }
}
