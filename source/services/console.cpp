/// @file console.cpp

#include <stdio.h>
#include "console.hpp"

namespace services
{
    console::console(core::game* p_game):
        service(p_game)
    {

    }

    bool console::initialise()
    {
        return true;
    }

    void console::update(utilities::gametime& p_gametime)
    {
        printf("Time: %f\n", p_gametime.get_total_time_in_seconds());
    }
}
