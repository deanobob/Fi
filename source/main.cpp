/// @file main.cpp

#include "game.hpp"

/// @brief The value to return when the application exits successfully
static constexpr auto EXIT_SUCCESS = 0;

/// @brief The entry point into the application
int main(int argc, char** argv)
{
    core::game g;
    g.initialise();
    g.run();

    return EXIT_SUCCESS;
}