/// @file cursor_subsystem.hpp
/// @brief Subsystem that manages the in-game cursor state

#ifndef CURSOR_SUBSYSTEM_HPP
#define CURSOR_SUBSYSTEM_HPP

#include "camera_controller.hpp"
#include "component_type.hpp"
#include "cursor_tool_type.hpp"
#include "entity_manager.hpp"
#include "message_bus.hpp"
#include "quadtree.hpp"
#include "quadtree_subsystem.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Subsystem that manages the in-game cursor state
    class cursor_subsystem
        : public core::quadtree_subsystem
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        /// @param p_entity_manager The game entity manager
        /// @param p_camera_controller The camera controller
        cursor_subsystem(
            core::message_bus* p_message_bus,
            core::entity_manager* p_entity_manager,
            core::camera_controller* p_camera_controller);
        /// @brief Default destructor
        virtual ~cursor_subsystem();

        bool initialise() override;

        void update(const utilities::gametime& gametime) override;

        void draw(camera* p_camera, double delta) override;

        void shutdown() override;

        bool pauseable() const override { return false; }

        void on_publish(message* p_message) override;

        private:
        /// @brief Pointer to the camera controller instance
        core::camera_controller* mp_camera_controller{nullptr};
        /// @brief The game mouse X coordinate
        int m_mouse_x{0};
        /// @brief The game mouse Y coordinate
        int m_mouse_y{0};
        /// @brief The active cursor tool
        core::cursor_tool_type m_active_cursor_tool{core::cursor_tool_type::none};
    };
} /// namespace core

#endif /// CURSOR_SUBSYSTEM_HPP
