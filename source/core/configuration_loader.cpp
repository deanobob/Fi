/// @file configuration_loader.cpp

#include "configuration_loader.hpp"
#include "plog/Log.h"

namespace core
{
    const utilities::configuration configuration_loader::load()
    {
        utilities::configuration config{};
        config.add("display_width", "1920");
        config.add("display_height", "1080");
        config.add("vsync", "true");
        config.add("fullscreen", "false");
        return config;
    }
}
