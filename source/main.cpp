/// @file main.cpp

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.hpp"

/// @brief The game instance
core::game g{};

/// @brief Handle Linux signals
/// @param signo The signal number
void sig_handler(int signo)
{
    // Request the game to exit
    g.exit();
}

/// @brief The entry point into the application
/// @param argc The number of arguments
/// @param argv The arguments
/// @return The exit code - 0 is success, 1 is failure
int main(int argc, char** argv)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR ||
        signal(SIGTERM, sig_handler) == SIG_ERR)
    {
        printf("Failed to handle signal\n");
        return EXIT_FAILURE;
    }

    g.run();

    return EXIT_SUCCESS;
}
