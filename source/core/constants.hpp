/// @file constants.hpp
/// @brief Base class for components

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/// @namespace core namespace
namespace core
{
    /// @brief The base constants class
    class constants
    {
        public:
        /// @brief Tile width
        static constexpr auto TILE_WIDTH {54.0f};

        private:
        /// @brief Default destructor
        virtual ~constants() = default;
    };
} /// namespace core

#endif /// CONSTANTS_HPP
