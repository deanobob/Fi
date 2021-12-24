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
        /// @brief The tile width
        static constexpr auto TILE_WIDTH {54.0f};
        /// @brief The world width
        static constexpr auto WORLD_WIDTH {10000};
        /// @brief The world height
        static constexpr auto WORLD_HEIGHT {10000};

        private:
        /// @brief Default destructor
        virtual ~constants() = default;
    };
} /// namespace core

#endif /// CONSTANTS_HPP
