/*
 * gametime.cpp
 *
 *  Created on: 12 Jan 2019
 *      Author: deanh
 */

#include "gametime.hpp"
#include "time.hpp"

namespace utilities
{
    gametime::gametime()
    {
        m_last_time = time::get_current_time_in_seconds();
    }

    void gametime::update()
    {
        double current_time = time::get_current_time_in_seconds();
        m_elapsed_time = current_time - m_last_time;
        m_total_time += m_elapsed_time;
        m_last_time = current_time;
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
} /* namespace utilities */
