/// @file catch_main.hpp

#define CATCH_CONFIG_RUNNER

#include "catch2/catch.hpp"
#include "plog/Log.h"
#include "plog/Initializers/RollingFileInitializer.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Appenders/ColorConsoleAppender.h"

int main( int argc, char* argv[] ) {

    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender{};
    plog::init(plog::debug, "log/malon_test.log").addAppender(&consoleAppender);

    return Catch::Session().run(argc, argv);
}
