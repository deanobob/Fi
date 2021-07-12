/// @file ui_service.cpp

#include "plog/Log.h"
#include "ui_service.hpp"

// TODO: remove when hack removed
#include "message_new_game.hpp"

namespace ui
{
    ui_service::ui_service(core::message_bus* p_message_bus)
        : service{p_message_bus}
    {
        mp_message_bus->subscribe(
            this,
            {
                messages::message_new_game::TYPE,
            }
        );
    }

    ui_service::~ui_service()
    {

    }

    bool ui_service::initialise()
    {
        /// @todo HACK simulating the user clicking a NEW GAME button
        auto message = messages::message_new_game{};
        mp_message_bus->send(&message);

        return true;
    }

    void ui_service::update(const utilities::gametime& gametime)
    {

    }

    void ui_service::draw(core::draw_manager* p_draw_manager)
    {

    }

    void ui_service::shutdown()
    {

    }
}
