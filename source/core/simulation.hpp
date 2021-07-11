/// @file simulation.hpp
/// @brief The core to the game simulation

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

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
        simulation();
        /// @brief Default destructor
        virtual ~simulation() = default;

        /// @brief Initialise the simulation
        bool initialise();

        /// @brief Called on every tick to update the simulation
        /// @param gametime The gametime
        void update(const utilities::gametime& gametime);

        /// @brief Shutdown the simulation
        void shutdown();

        /// @brief Add subsystem to simulation
        /// @param service The subsystem to add
        void add_subsystem(std::unique_ptr<subsystem> subsystem);
        
        void on_publish(core::message* p_message) override;

        private:
        /// @brief Container for subsystem
        std::list<std::unique_ptr<subsystem> > m_subsystems{};
        /// @brief The simulation message bus
        std::unique_ptr<core::message_bus> mp_message_bus{nullptr};
        /// @brief The entity manager
        std::unique_ptr<core::entity_manager> mp_entity_manager{nullptr};
    };
} /// namespace core

#endif /// SIMULATION_HPP
