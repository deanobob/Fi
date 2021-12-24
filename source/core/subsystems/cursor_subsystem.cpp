/// @file cursor_subsystem.cpp

#include <math.h>
#include "plog/Log.h"
#include "component_type.hpp"
#include "constants.hpp"
#include "cursor_subsystem.hpp"
#include "message_sim_mouse_move.hpp"
#include "message_set_cursor_tool.hpp"

namespace core
{
    cursor_subsystem::cursor_subsystem(
        core::message_bus* p_message_bus,
        core::entity_manager* p_entity_manager,
        core::camera_controller* p_camera_controller)
        : quadtree_subsystem{p_message_bus, p_entity_manager, {component_type::body}}
        , mp_camera_controller{p_camera_controller}
    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_set_cursor_tool::TYPE,
                messages::message_sim_mouse_move::TYPE,
            }
        );
    }

    cursor_subsystem::~cursor_subsystem()
    {
        mp_message_bus->unsubscribe(this);
    }

    bool cursor_subsystem::initialise()
    {
        return true;
    }

    void cursor_subsystem::update(const utilities::gametime& gametime)
    {

    }

    void cursor_subsystem::draw(camera* p_camera, double delta)
    {
        if (m_active_cursor_tool != core::cursor_tool_type::none)
        {
            auto x = static_cast<float>(m_mouse_x);
            auto y = static_cast<float>(m_mouse_y);
            // offset by tile margins
            x -= ((x >= 0) ? 0 : constants::TILE_WIDTH) + std::fmod(x, constants::TILE_WIDTH);
            y -= ((y >= 0) ? 0 : constants::TILE_WIDTH) + std::fmod(y, constants::TILE_WIDTH);

            p_camera->add_renderable(
                std::make_unique<render::renderable_rectangle>(
                    x,
                    y,
                    constants::TILE_WIDTH,
                    constants::TILE_WIDTH,
                    0,
                    utilities::colors::white,
                    1));

            switch (m_active_cursor_tool)
            {
                case core::cursor_tool_type::track_0_deg:
                    p_camera->add_renderable(
                        std::make_unique<render::renderable_rectangle>(
                            x,
                            y + 25,
                            constants::TILE_WIDTH,
                            1,
                            0,
                            utilities::colors::white, 2));
                    break;
                case core::cursor_tool_type::track_45_deg:
                    p_camera->add_renderable(
                        std::make_unique<render::renderable_line>(
                            x,
                            y,
                            x + constants::TILE_WIDTH,
                            y + constants::TILE_WIDTH,
                            utilities::colors::white,
                            2));
                    break;
                case core::cursor_tool_type::track_90_deg:
                    p_camera->add_renderable(
                        std::make_unique<render::renderable_rectangle>(
                            x + 25,
                            y,
                            1,
                            constants::TILE_WIDTH,
                            0,
                            utilities::colors::white, 2));
                    break;
                case core::cursor_tool_type::track_135_deg:
                    p_camera->add_renderable(
                        std::make_unique<render::renderable_line>(
                            x + 50,
                            y,
                            x,
                            y + constants::TILE_WIDTH,
                            utilities::colors::white,
                            2));
                    break;
                default:
                    break;
            }
        }
        p_camera->add_renderable(
            std::make_unique<render::renderable_text>(
                m_mouse_x,
                m_mouse_y - 35,
                1,
                std::string("Tooltip!"),
                utilities::colors::white,
                ui::text_alignment::centre));
        p_camera->add_renderable(
            std::make_unique<render::renderable_circle>(
                m_mouse_x,
                m_mouse_y,
                40.f,
                utilities::colors::blue,
                2));
    }

    void cursor_subsystem::shutdown()
    {

    }

    void cursor_subsystem::on_publish(message* p_message)
    {
        if (p_message->get_type() == messages::message_set_cursor_tool::TYPE)
        {
            const auto p_set_cursor_tool_message = dynamic_cast<messages::message_set_cursor_tool*>(p_message);
            m_active_cursor_tool = p_set_cursor_tool_message->get_cursor_tool_type();
        }
        else if (p_message->get_type() == messages::message_sim_mouse_move::TYPE)
        {
            const auto p_sim_mouse_move_message = dynamic_cast<messages::message_sim_mouse_move*>(p_message);
            m_mouse_x = p_sim_mouse_move_message->get_x();
            m_mouse_y = p_sim_mouse_move_message->get_y();
        }
        else
        {
            component_subsystem::on_publish(p_message);
        }
    }
}
