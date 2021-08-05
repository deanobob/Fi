/// @file simulation.cpp

#include "plog/Log.h"
#include "entity.hpp"
#include "body_component.hpp"
#include "message_open_window.hpp"
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
        add_subsystem(std::make_unique<render_subsystem>(mp_message_bus.get(), mp_entity_manager.get()));
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
        auto p_camera = std::make_unique<core::camera>();
        m_cameras_by_tag.emplace("main", p_camera.get());
        m_cameras.emplace(p_camera->get_id(), std::move(p_camera));

        // Initialise test entities
        {
            auto entity{std::make_unique<core::entity>()};
            entity->add_component(std::make_unique<core::body_component>(utilities::vector2{10, 10}, utilities::vector2{5, 5}));
            entity->add_component(std::make_unique<core::render_component>());
            mp_entity_manager->put(std::move(entity));
        }
        {
            auto entity{std::make_unique<core::entity>()};
            entity->add_component(std::make_unique<core::body_component>(utilities::vector2{90, 10}, utilities::vector2{5, 5}));
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
    }

    void simulation::draw()
    {
        for (const auto& camera_iter : m_cameras)
        {
            for (auto& subsystem : m_subsystems)
            {
                subsystem->draw(camera_iter.second.get());
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
        const auto camera_iter = m_cameras.find(camera_id);
        if (camera_iter != m_cameras.end())
        {
            return camera_iter->second.get();
        }

        return nullptr;
    }

    core::camera* simulation::get_camera(const std::string& camera_tag) const
    {
        const auto camera_iter = m_cameras_by_tag.find(camera_tag);
        if (camera_iter != m_cameras_by_tag.end())
        {
            return camera_iter->second;
        }

        return nullptr;
    }

    void simulation::on_publish(core::message* p_message)
    {

    }

    void simulation::on_mouse_down(int position_x, int position_y)
    {
        auto p_camera = std::make_unique<core::camera>();
        p_camera->set_position({position_x, position_y});

        auto message = messages::message_open_window{p_camera.get()};
        m_cameras.emplace(p_camera->get_id(), std::move(p_camera));
        mp_message_bus->send(&message);
    }
}
