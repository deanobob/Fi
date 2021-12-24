/// @file map_subsystem.hpp
/// @brief Subsystem that manages the map

#ifndef MAP_SUBSYSTEM_HPP
#define MAP_SUBSYSTEM_HPP

#include "component_subsystem.hpp"
#include "component_type.hpp"
#include "constants.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Base class for component subsystems
    class map_subsystem
        : public core::component_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        map_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager);
        /// @brief Default destructor
        virtual ~map_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return true; }

        private:
        /// @brief The tile width
        static constexpr auto m_tile_width {constants::TILE_WIDTH};
        /// @brief The tile height
        static constexpr auto m_tile_height {constants::TILE_WIDTH};
        /// @brief The number of tiles on the X axis
        static constexpr auto m_num_tiles_x {50};
        /// @brief The number of tiles on the Y axis
        static constexpr auto m_num_tiles_y {50};
        /// @brief The map width
        static constexpr auto m_map_width {m_tile_width * m_num_tiles_x};
        /// @brief The map height
        static constexpr auto m_map_height {m_tile_width * m_num_tiles_x};

        /// @brief The world width
        const int m_world_width;
        /// @brief The world height
        const int m_world_height;

        /// @brief Contains the tile type for each tile in the map
        uint8_t m_map[m_num_tiles_x * m_num_tiles_y] {};

        /// @brief Get the tilemap X and Y coordinates given a world coordinate
        /// @param x The x world coordinate
        /// @param y The y world coordinate
        /// @return Tuple containing the tilemap X and Y coordinates
        std::tuple<int, int> get_tile_at(float x, float y) const;

        /// @brief Get the position of the left edge of the map
        /// @return The left position of the map
        float get_map_left() const;

        /// @brief Get the position of the top edge of the map
        /// @return The top position of the map
        float get_map_top() const;
    };
} /// namespace core

#endif /// MAP_SUBSYSTEM_HPP
