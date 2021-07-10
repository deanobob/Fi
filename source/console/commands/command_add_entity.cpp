/// @file command_add_entity.cpp

#include "plog/Log.h"
#include "body_component.hpp"
#include "command_add_entity.hpp"
#include "game.hpp"
#include "render_component.hpp"

namespace console
{
    command_add_entity::command_add_entity(core::entity_manager* p_entity_manager):
        mp_entity_manager{p_entity_manager}
    {

    }

    const std::vector<std::string> command_add_entity::get_command_names() const
    {
        return {"add_entity"};
    }

    void command_add_entity::execute(const std::vector<std::string>& args) const
    {
        if (args.size() != 2)
        {
            LOG_DEBUG << "Invalid command. Requires 1 argument";
            return;
        }

        const auto tag{args[1]};
        auto entity{std::make_unique<core::entity>(tag)};
        entity->add_component(std::make_unique<core::body_component>());
        entity->add_component(std::make_unique<core::render_component>());
        mp_entity_manager->put(std::move(entity));
    }
}
