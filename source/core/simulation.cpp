/// @file simulation.cpp

#include "plog/Log.h"
#include "simulation.hpp"

namespace core
{
    simulation::simulation()
        : mp_message_bus{std::make_unique<message_bus>()}
        , mp_entity_manager{std::make_unique<entity_manager>(mp_message_bus.get())}
    {

    }

    bool simulation::initialise()
    {
        PLOG_DEBUG << "Initialised simulation";
        mp_entity_manager->initialise();
       
        return true;
    }

    void simulation::update(const utilities::gametime& gametime)
    {
        mp_entity_manager->update(gametime);
    }

    void simulation::shutdown()
    {
        mp_entity_manager->shutdown();
        PLOG_DEBUG << "Shutdown simulation";
    }

    void simulation::add_subsystem(std::unique_ptr<subsystem> subsystem)
    {
        m_subsystems.push_back(std::move(subsystem));
    }
        
    void simulation::on_publish(core::message* p_message)
    {

    }
}