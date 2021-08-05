/// @file simulation.hpp
/// @brief The core to the game simulation

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <map>
#include "camera.hpp"
#include "entity_manager.hpp"
#include "gametime.hpp"
#include "subsystem.hpp"
#include "subscriber.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The base simulation class
    class simulation
        : public core::subscriber
    {
        public:
        /// @brief Constructor
        /// @param p_message_bus The game message bus
        simulation(core::message_bus* p_message_bus);
        /// @brief Default destructor
        virtual ~simulation();

        /// @brief Initialise the simulation
        /// @return True on success, false on failure
        bool initialise();

        /// @brief Called on every tick to update the simulation
        /// @param gametime The gametime
        void update(const utilities::gametime& gametime);

        /// @brief Called on every frame render
        void draw();

        /// @brief Shutdown the simulation
        void shutdown();

        /// @brief Add subsystem to simulation
        /// @param subsystem The subsystem to add
        void add_subsystem(std::unique_ptr<subsystem> subsystem);

        /// @brief Get a camera by id
        /// @param camera_id The camera ID
        /// @return Pointer to the camera or nullptr if not found
        core::camera* get_camera(const uint32_t camera_id) const;

        /// @brief Get a camera by tag
        /// @param camera_tag The camera tag
        /// @return Pointer to the camera or nullptr if not found
        core::camera* get_camera(const std::string& camera_tag) const;

        void on_publish(core::message* p_message) override;

        /// @brief A mouse down event has been received
        /// @param position_x The mouse X position
        /// @param position_y The mouse Y position
        void on_mouse_down(int position_x, int position_y);

        private:
        /// @brief Container for subsystem
        std::list<std::unique_ptr<subsystem> > m_subsystems{};
        /// @brief The simulation message bus
        std::unique_ptr<core::message_bus> mp_message_bus{nullptr};
        /// @brief The entity manager
        std::unique_ptr<core::entity_manager> mp_entity_manager{nullptr};
        /// @brief The simulation cameras
        std::map<const uint32_t, std::unique_ptr<core::camera> > m_cameras{};
        /// @brief Lookup map of cameras stored by tag name
        std::map<const std::string, core::camera*> m_cameras_by_tag{};
    };
} /// namespace core

#endif /// SIMULATION_HPP
