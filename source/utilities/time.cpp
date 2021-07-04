/// @file time.cpp

#include <chrono>
#include <unistd.h>
#include "time.hpp"

namespace utilities
{
    double time::get_current_time_in_seconds()
    {
        const auto time_now_in_nano_seconds = std::chrono::high_resolution_clock::now().time_since_epoch();
        return static_cast<double>(time_now_in_nano_seconds.count()) / static_cast<double>(NANOSECONDS_IN_ONE_SECOND);
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
