/// @file time.cpp

#include <sys/time.h>
#include <unistd.h>
#include "time.hpp"

namespace utilities
{
    double time::get_current_time_in_seconds()
    {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        return tv.tv_sec + (tv.tv_usec / MICROSECONDS_IN_ONE_SECOND);
    }

    void time::sleep_sec(uint32_t seconds)
    {
        usleep(seconds * MICROSECONDS_IN_ONE_SECOND);
    }

    void time::sleep_msec(uint32_t milliseconds)
    {
        usleep(milliseconds * MICROSECONDS_IN_ONE_MILLISECOND);
    }
}
