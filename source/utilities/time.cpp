/// @file time.cpp

#include <unistd.h>
#include "time.hpp"

namespace utilities
{
    void time::sleep_sec(uint32_t seconds)
    {
        usleep(seconds * MICROSECONDS_IN_ONE_SECOND);
    }

    void time::sleep_msec(uint32_t milliseconds)
    {
        usleep(milliseconds * MICROSECONDS_IN_ONE_MILLISECOND);
    }
}
