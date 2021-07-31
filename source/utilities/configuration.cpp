/// @file configuration.cpp

#include <algorithm>
#include "plog/Log.h"
#include "configuration.hpp"

namespace utilities
{
    void configuration::add(const std::string& key, const std::string& value)
    {
        m_cache[key] = value;
    }

    const std::string& configuration::get_string(const std::string& key, const std::string& default_value) const
    {
        const auto& config_iter = m_cache.find(key);
        if (config_iter != m_cache.end())
        {
            return config_iter->second;
        }

        return default_value;
    }

    int configuration::get_int(const std::string& key, int default_value) const
    {
        const auto& config_iter = m_cache.find(key);
        if (config_iter != m_cache.end())
        {
            try
            {
                return std::stoi(config_iter->second);
            }
            catch (...) {}
        }

        return default_value;
    }

    float configuration::get_float(const std::string& key, float default_value) const
    {
        const auto& config_iter = m_cache.find(key);
        if (config_iter != m_cache.end())
        {
            try
            {
                return std::stof(config_iter->second);
            }
            catch (...) {}
        }

        return default_value;
    }

    double configuration::get_double(const std::string& key, double default_value) const
    {
        const auto& config_iter = m_cache.find(key);
        if (config_iter != m_cache.end())
        {
            try
            {
                return std::stod(config_iter->second);
            }
            catch (...) {}
        }

        return default_value;
    }

    bool configuration::get_bool(const std::string& key, bool default_value) const
    {
        LOG_DEBUG << "key: " << key << ", default_value: " << default_value;

        const auto& config_iter = m_cache.find(key);
        if (config_iter != m_cache.end())
        {
            auto str_val = config_iter->second;
            std::transform(str_val.begin(), str_val.end(), str_val.begin(), ::tolower);
            LOG_DEBUG << "value: " << str_val;
            return str_val == "true";
        }

        return default_value;
    }
}
