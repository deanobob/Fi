/// @file time.hpp
/// @brief Contains time utilities

#ifndef TIME_HPP
#define TIME_HPP

#include <stdint.h>

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that contains time utilities
    class time
    {
        public:
        /// @brief The number of milliseconds in one second
        static constexpr auto MILLISECONDS_IN_ONE_SECOND{1000.0};
        /// @brief The number of microseconds in one second
        static constexpr auto MICROSECONDS_IN_ONE_SECOND{1000000.0};
        /// @brief The number of microseconds in one millisecond
        static constexpr auto MICROSECONDS_IN_ONE_MILLISECOND{1000.0};

        /// @brief Get current time in seconds
        /// @return The current time in seconds
        static double get_current_time_in_seconds();

        /// @brief Sleeps for n seconds
        /// @param seconds The number of seconds to sleep for
        static void sleep_sec(uint32_t seconds);

        /// @brief Sleeps for n microseconds
        /// @param milliseconds The number of microseconds to sleep for
        static void sleep_msec(uint32_t microseconds);

        private:
        /// @brief Default constructor
        time() = default;
        /// @brief Default destructor
        ~time() = default;
    };
} /// namespace utilities

#endif /// UTILITIES_HPP
