/// @file simulation.cpp

#include "plog/Log.h"
#include "entity.hpp"
#include "body_component.hpp"
#include "clickable_component.hpp"
#include "clickable_subsystem.hpp"
#include "movement_component.hpp"
#include "movement_subsystem.hpp"
#include "rectangle.hpp"
#include "render_component.hpp"
#include "render_subsystem.hpp"
#include "simulation.hpp"
#include "vector2.hpp"

namespace core
{
    simulation::simulation(core::message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
        , mp_entity_manager{std::make_unique<entity_manager>(mp_message_bus)}
    {
        add_subsystem(
            std::make_unique<clickable_subsystem>(
                mp_message_bus,
                mp_entity_manager.get(),
                &m_camera_controller));
        add_subsystem(
            std::make_unique<movement_subsystem>(
                mp_message_bus,
                mp_entity_manager.get()));
        add_subsystem(
            std::make_unique<render_subsystem>(
                mp_message_bus,
                mp_entity_manager.get()));
    }

    simulation::~simulation()
    {
        m_subsystems.clear();
        mp_entity_manager.reset(nullptr);
    }

    bool simulation::initialise()
    {
        mp_entity_manager->initialise();

        for (auto& subsystem : m_subsystems)
        {
            subsystem->initialise();
        }

        // Initialise main camera
        m_camera_controller.add_camera(std::make_unique<core::camera>(utilities::vector2{5000, 5000}), "main");

        // Initialise test entities
        for (int i = 0; i < 10; i++)
        {
            auto entity{std::make_unique<core::entity>()};
            entity->add_component(std::make_unique<core::body_component>(
                utilities::vector2{5000, 5000},
                utilities::vector2{50, 50},
                rand() % 360));
            entity->add_component(std::make_unique<core::movement_component>((rand() % 300) - 150));
            entity->add_component(std::make_unique<core::clickable_component>());
            entity->add_component(std::make_unique<core::render_component>());
            mp_entity_manager->put(std::move(entity));
        }

        PLOG_DEBUG << "Initialised simulation";
        return true;
    }

    void simulation::update(const utilities::gametime& gametime)
    {
        mp_entity_manager->update(gametime);

        for (auto& subsystem : m_subsystems)
        {
            subsystem->update(gametime);
        }

        for (auto& p_camera : m_camera_controller.get_cameras())
        {
            p_camera->update(gametime);
        }
    }

    void simulation::draw(double delta)
    {
        for (const auto& p_camera : m_camera_controller.get_cameras())
        {
            for (auto& subsystem : m_subsystems)
            {
                subsystem->draw(p_camera, delta);
            }
        }
    }

    void simulation::shutdown()
    {
        for (auto& subsystem : m_subsystems)
        {
            subsystem->shutdown();
        }

        mp_entity_manager->shutdown();
        PLOG_DEBUG << "Shutdown simulation";
    }

    void simulation::add_subsystem(std::unique_ptr<subsystem> subsystem)
    {
        m_subsystems.push_back(std::move(subsystem));
    }

    core::camera* simulation::get_camera(const uint32_t camera_id) const
    {
        return m_camera_controller.get_camera_by_id(camera_id);
    }

    core::camera* simulation::get_camera(const std::string& camera_tag) const
    {
        return m_camera_controller.get_camera_by_tag(camera_tag);
    }

    void simulation::on_publish(core::message* p_message)
    {

    }
}
