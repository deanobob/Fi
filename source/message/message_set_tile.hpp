/// @file message_set_tile.hpp
/// @brief Message that requests the map to change a tile to a given type

#ifndef MESSAGE_SET_TILE_HPP
#define MESSAGE_SET_TILE_HPP

#include "message.hpp"

/// @namespace messages namespace
namespace messages
{
    /// @brief Message that notifies the game that the window has resized
    class message_set_tile
        : public core::message
    {
        public:
        /// @brief Construct a new message set tile object
        /// @param position_x The position X
        /// @param position_y The position Y
        /// @param tile_type The tile type
        message_set_tile(int position_x, int position_y, uint8_t tile_type)
            : m_position_x{position_x}
            , m_position_y{position_y}
            , m_tile_type{tile_type}
        {

        }

        /// @brief The message type
        static constexpr auto TYPE { "SET_TILE" };

        const std::string get_type() const override { return TYPE; };

        /// @brief Get the position X position
        /// @return The position X position
        int get_position_x() const
        {
            return m_position_x;
        }

        /// @brief Get the position Y position
        /// @return The position Y position
        int get_position_y() const
        {
            return m_position_y;
        }

        /// @brief Get the tile type
        /// @return The tile type
        uint8_t get_tile_type() const
        {
            return m_tile_type;
        }

        private:
        /// @brief The x tile position
        const int m_position_x;
        /// @brief The y tile position
        const int m_position_y;
        /// @brief The tile type
        const uint8_t m_tile_type;
    };
} /// namespace messages

#endif /// MESSAGE_SET_TILE_HPP
