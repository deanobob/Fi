/// @file draw_manager.cpp

#include <memory>
#include "plog/Log.h"
#include "draw_manager.hpp"
#include "game.hpp"
#include "time.hpp"


#include "entity.hpp"
#include "body_component.hpp"

namespace core
{
    draw_manager::draw_manager(game* p_game)
        : component_service{p_game, component_type::body}
    {
        mp_renderer = p_game->get_system_interface()->get_renderer();
        assert(mp_renderer != nullptr);

        mp_renderer->add_event_listener(this);
    }

    draw_manager::~draw_manager()
    {
        mp_renderer->remove_event_listener(this);
    }

    bool draw_manager::initialise()
    {
        framework::window_properties window_properties{};

        auto e = std::make_unique<entity>();
        e->add_component(std::make_unique<body_component>());
        get_entity_manager()->put(std::move(e));

        return mp_renderer->initialise()
            && mp_renderer->create_window(window_properties);
    }

    void draw_manager::update(const utilities::gametime& gametime)
    {
        mp_renderer->process_events();
    }

    void draw_manager::draw(double delta)
    {
        mp_renderer->clear();

        // draw stuff here
        utilities::time::sleep_msec(16);

        mp_renderer->flip();
    }

    void draw_manager::shutdown()
    {
        mp_renderer->destroy_window();
        mp_renderer->shutdown();
    }

    void draw_manager::on_display_close()
    {
        mp_game->exit();
    }

    void draw_manager::on_display_gained_focus()
    {
        PLOG_DEBUG << "Focus gained";
    }

    void draw_manager::on_display_lost_focus()
    {
        PLOG_DEBUG << "Focus lost";
    }
}
