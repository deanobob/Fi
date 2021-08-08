/// @file clickable_subsystem.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "component_type.hpp"
#include "clickable_subsystem.hpp"
#include "follow_camera.hpp"
#include "message_open_window.hpp"
#include "message_sim_mouse_event.hpp"

namespace core
{
    clickable_subsystem::clickable_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        core::camera_controller* p_camera_controller)
        : quadtree_subsystem{p_message_bus, p_entity_manager, {component_type::body | component_type::clickable}}
        , mp_camera_controller{p_camera_controller}
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

    void clickable_subsystem::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_sim_mouse_event::TYPE)
        {
            const auto p_sim_message = dynamic_cast<messages::message_sim_mouse_event*>(p_message);
            const auto mouse_point = utilities::rectangle{
                static_cast<float>(p_sim_message->get_x()),
                static_cast<float>(p_sim_message->get_y()),
                1.0f,
                1.0f};
            for (auto& p_entity : get_entities_in_region(mouse_point))
            {
                auto p_camera = std::make_unique<core::follow_camera>(p_entity);
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
