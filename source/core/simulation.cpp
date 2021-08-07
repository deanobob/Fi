/// @file simulation.cpp

#include "plog/Log.h"
#include "entity.hpp"
#include "body_component.hpp"
#include "clickable_component.hpp"
#include "clickable_subsystem.hpp"
#include "physics_component.hpp"
#include "physics_subsystem.hpp"
#include "rectangle.hpp"
#include "render_component.hpp"
#include "render_subsystem.hpp"
#include "simulation.hpp"
#include "vector2.hpp"

namespace core
{
    simulation::simulation(core::message_bus* p_message_bus)
        : mp_message_bus{p_message_bus}
        , mp_entity_manager{std::make_unique<entity_manager>(mp_message_bus.get())}
    {
        add_subsystem(
            std::make_unique<clickable_subsystem>(
                mp_message_bus.get(),
                mp_entity_manager.get(),
                &m_camera_controller));
        add_subsystem(
            std::make_unique<physics_subsystem>(
                mp_message_bus.get(),
                mp_entity_manager.get()));
        add_subsystem(
            std::make_unique<render_subsystem>(
                mp_message_bus.get(),
                mp_entity_manager.get()));
    }

    simulation::~simulation()
    {
        m_subsystems.clear();
        mp_entity_manager.reset(nullptr);
        mp_message_bus.reset(nullptr);
    }

    bool simulation::initialise()
    {
        PLOG_DEBUG << "Initialised simulation";
        mp_entity_manager->initialise();

        for (auto& subsystem : m_subsystems)
        {
            subsystem->initialise();
        }

        // Initialise main camera
        m_camera_controller.add_camera(std::make_unique<core::camera>(), "main");

        // Initialise test entities
        {
            auto entity{std::make_unique<core::entity>()};
            entity->add_component(std::make_unique<core::body_component>(utilities::vector2{10, 10}, utilities::vector2{50, 50}));
            entity->add_component(std::make_unique<core::physics_component>(utilities::vector2{50, 0}));
            entity->add_component(std::make_unique<core::clickable_component>());
            entity->add_component(std::make_unique<core::render_component>());
            mp_entity_manager->put(std::move(entity));
        }
        {
            auto entity{std::make_unique<core::entity>()};
            entity->add_component(std::make_unique<core::body_component>(utilities::vector2{90, 10}, utilities::vector2{50, 50}));
            entity->add_component(std::make_unique<core::physics_component>(utilities::vector2{50, 50}));
            entity->add_component(std::make_unique<core::clickable_component>());
            entity->add_component(std::make_unique<core::render_component>());
            mp_entity_manager->put(std::move(entity));
        }

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
