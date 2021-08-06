/// @file clickable_subsystem.cpp

#include "plog/Log.h"
#include "camera.hpp"
#include "body_component.hpp"
#include "component_type.hpp"
#include "clickable_subsystem.hpp"
#include "message_open_window.hpp"
#include "message_sim_mouse_event.hpp"

namespace core
{
    clickable_subsystem::clickable_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        core::camera_controller* p_camera_controller)
        : component_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::clickable}}
        , mp_camera_controller{p_camera_controller}
        , m_quadtree{utilities::rectangle{0, 0, 1000, 1000}} //TODO: determine world size
    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_sim_mouse_event::TYPE
            }
        );
    }

    clickable_subsystem::~clickable_subsystem()
    {

    }

    bool clickable_subsystem::initialise()
    {
        return true;
    }

    void clickable_subsystem::update(const utilities::gametime& gametime)
    {

    }

    void clickable_subsystem::draw(camera* p_camera, double delta)
    {

    }

    void clickable_subsystem::shutdown()
    {

    }

    void clickable_subsystem::on_entity_added(entity* p_entity)
    {
        // TODO: register for events indicating an entity has moved, and update the quadtree.
        const auto& p_body = p_entity->get_component<body_component>(component_type::body);
        const auto& position = p_body->get_position();
        const auto& size = p_body->get_size();
        m_quadtree.insert(p_entity->get_id(), {position.x, position.y, size.x, size.y});
    }

    void clickable_subsystem::on_entity_removed(entity* p_entity)
    {
        m_quadtree.remove(p_entity->get_id());
    }

    void clickable_subsystem::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_sim_mouse_event::TYPE)
        {
            const auto p_sim_message = dynamic_cast<messages::message_sim_mouse_event*>(p_message);
            for (auto& entity_id : m_quadtree.query({
                static_cast<float>(p_sim_message->get_x()),
                static_cast<float>(p_sim_message->get_y()),
                1.0f,
                1.0f}))
            {
                auto p_camera = std::make_unique<core::camera>();
                p_camera->set_position({p_sim_message->get_x(), p_sim_message->get_y()});

                auto message = messages::message_open_window{p_camera.get()};
                mp_camera_controller->add_camera(std::move(p_camera));
                mp_message_bus->send(&message);
            }
        }
        else
        {
            component_subsystem::on_publish(p_message);
        }
    }
}
