/// @file catch_main.cpp

#define CATCH_CONFIG_RUNNER

#include "catch2/catch.hpp"
#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Appenders/ColorConsoleAppender.h"

/// @brief Catch2 test main function
/// @param argc The number of command line arguments
/// @param argv The command line arguments
/// @return Catch session result - zero indicates success
int main(int argc, char* argv[]) {

    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender{};
    plog::init(plog::debug, "log/malon_test.log").addAppender(&consoleAppender);

    return Catch::Session().run(argc, argv);
}
