/// @file gametime.cpp

#include "gametime.hpp"
#include "time.hpp"

namespace utilities
{
    void gametime::add_elapsed_time_in_seconds(double elapsed_time)
    {
        m_elapsed_time = elapsed_time;
        m_total_time += m_elapsed_time;
    }

    double gametime::get_elapsed_time_in_seconds() const
    {
        return m_elapsed_time;
    }

    double gametime::get_total_time_in_seconds() const
    {
        return m_total_time;
    }

    double gametime::get_elapsed_time_in_milliseconds() const
    {
        return m_elapsed_time * time::MILLISECONDS_IN_ONE_SECOND;
    }

    double gametime::get_total_time_in_milliseconds() const
    {
        return m_total_time * time::MILLISECONDS_IN_ONE_SECOND;
    }
} /// namespace utilities
