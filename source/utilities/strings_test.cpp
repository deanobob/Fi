/// @file strings.cpp

#include "catch2/catch.hpp"
#include "strings.hpp"

TEST_CASE("utilities/strings.hpp - Tokenise", "[utilities]")
{
    SECTION("1 Tokenise string by default space delimiter")
    {
        const std::string text_to_tokenize{"abcde efghij klmno"};
        const auto tokens = utilities::strings::tokenise(text_to_tokenize);
        REQUIRE(tokens.size() == 3);
        REQUIRE(tokens[0] == "abcde");
        REQUIRE(tokens[1] == "efghij");
        REQUIRE(tokens[2] == "klmno");
    }

    SECTION("2 Tokenise string by comma delimiter")
    {
        const std::string text_to_tokenize{"abcde,efghij,klmno"};
        const auto tokens = utilities::strings::tokenise(text_to_tokenize, ',');
        REQUIRE(tokens.size() == 3);
        REQUIRE(tokens[0] == "abcde");
        REQUIRE(tokens[1] == "efghij");
        REQUIRE(tokens[2] == "klmno");
    }

    SECTION("3 Tokenise string with no delimiter match")
    {
        const std::string text_to_tokenize{"abcde,efghij,klmno"};
        const auto tokens = utilities::strings::tokenise(text_to_tokenize, ' ');
        REQUIRE(tokens.size() == 1);
        REQUIRE(tokens[0] == "abcde,efghij,klmno");
    }
}
