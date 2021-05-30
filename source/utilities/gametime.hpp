/// @file gametime.hpp
/// @brief The gametime base class

#ifndef GAMETIME_HPP_
#define GAMETIME_HPP_

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that maintains a record of the elapsed time of the previous frame
    /// and the total time since the game launched
    class gametime
    {
        public:
        /// @brief Constructor
        gametime();

        /// @brief Updates the elapsed time and total run time
        void update();

        /// @brief Gets the elapsed time since the last tick
        /// @return The elapased time in seconds
        double get_elapsed_time_in_seconds() const;
        /// @brief Gets the total run time since the game launched
        /// @return The total time in seconds
        double get_total_time_in_seconds() const;
        /// @brief Gets the elapsed time of the last tick
        /// @return The elapased time in milliseconds
        double get_elapsed_time_in_milliseconds() const;
        /// @brief Gets the total run time since the game launched
        /// @return The total time in milliseconds
        double get_total_time_in_milliseconds() const;

        private:
        /// @brief The last frame time in seconds
        double m_last_time{0.0};
        /// @brief The elapsed time of the last tick
        double m_elapsed_time{0.0};
        /// @brief The total time since the game launched
        double m_total_time{0.0};
    };
} /// namespace utilities

#endif /// GAMETIME_HPP
