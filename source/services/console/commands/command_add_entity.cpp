/// @file command_add_entity.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "command_add_entity.hpp"
#include "entity_manager.hpp"
#include "game.hpp"

namespace services
{
    command_add_entity::command_add_entity(core::game* p_game):
        mp_game{p_game}
    {

    }

    const std::vector<std::string> command_add_entity::get_command_names() const
    {
        return {"add_entity"};
    }

    void command_add_entity::execute(const std::vector<std::string>& args) const
    {
        auto p_entity_manager = mp_game->get_service<services::entity_manager>(core::service_type::entity_manager);
        if (!p_entity_manager)
        {
            LOG_DEBUG << "Failed to get entity manager";
            return;
        }

        if (args.size() != 2)
        {
            LOG_DEBUG << "Invalid command. Requires 1 argument";
            return;
        }

        const auto tag{args[1]};
        auto entity{std::make_unique<core::entity>(tag)};
        entity->add_component(std::make_unique<core::body_component>());
        p_entity_manager->put(std::move(entity));
    }
}
