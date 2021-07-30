/// @file configuration.hpp
/// @brief Project configuration

#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <map>
#include <string>

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Class that contains project configuration
    class configuration
    {
        public:
        /// @brief Add configuration key pair
        /// @param key The configuration key
        /// @param value The configuration value
        void add(const std::string& key, const std::string& value);

        /// @brief Get a configuration value
        /// @param key The configuration key
        /// @param default_value The default value if the property isn't defined
        /// @return The value as a string
        const std::string& get_string(const std::string& key, const std::string& default_value = "") const;

        /// @brief Get a configuration value
        /// @param key The configuration key
        /// @param default_value The default value if the property isn't defined
        /// @return The value as an integer
        int get_int(const std::string& key, int default_value = 0) const;

        /// @brief Get a configuration value
        /// @param key The configuration key
        /// @param default_value The default value if the property isn't defined
        /// @return The value as a float
        float get_float(const std::string& key, float default_value = 0.0f) const;

        /// @brief Get a configuration value
        /// @param key The configuration key
        /// @param default_value The default value if the property isn't defined
        /// @return The value as a double
        double get_double(const std::string& key, double default_value = 0.0) const;

        /// @brief Get a configuration value
        /// @param key The configuration key
        /// @param default_value The default value if the property isn't defined
        /// @return The value as a bool
        bool get_bool(const std::string& key, bool default_value = false) const;

        private:
        /// @brief Configuration storage
        std::map<std::string, std::string> m_cache{};
    };
} /// namespace utilities

#endif /// CONFIGURATION_HPP
