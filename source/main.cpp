/// @file main.cpp

#include <signal.h>
#include <stdlib.h>
#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Appenders/ColorConsoleAppender.h"
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
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender{};
    plog::init(plog::debug, "Log.txt").addAppender(&consoleAppender);

    if (signal(SIGINT, sig_handler) == SIG_ERR ||
        signal(SIGTERM, sig_handler) == SIG_ERR)
    {
        PLOGD << "Failed to handle signal";
        return EXIT_FAILURE;
    }

    g.run();

    return EXIT_SUCCESS;
}
