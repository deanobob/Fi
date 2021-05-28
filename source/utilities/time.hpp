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
        /// @brief The number of microseconds in one second
        static const uint32_t MICROSECONDS_IN_ONE_SECOND{1000000};
        /// @brief The number of microseconds in one millisecond
        static const uint32_t MICROSECONDS_IN_ONE_MILLISECOND{1000};

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
