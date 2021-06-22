/// @file entity.cpp

#include "entity.hpp"

/// @namespace core namespace
namespace core
{
    entity_id entity::next_entity_id{1};

    entity::entity(std::string tag) :
        m_id{next_entity_id++},
        m_tag{tag}
    {

    }

    void entity::update(utilities::gametime& gametime)
    {
        if (m_update_on_tick)
        {
            on_update(gametime);
        }
    }

    bool entity::add_component(std::unique_ptr<component> component)
    {
        auto type = component->get_type();
        m_components.emplace(component->get_type(), std::move(component));
        m_component_mask |= type;
        return true;
    }

    bool entity::remove_component(component_type component_type)
    {
        const auto component_iter = m_components.find(component_type);
        if (component_iter != m_components.end())
        {
            m_components.erase(component_iter);
            m_component_mask &= ~component_type;
            return true;
        }

        return false;
    }

    entity_id entity::get_id() const
    {
        return m_id;
    }

    const std::string& entity::get_tag() const
    {
        return m_tag;
    }

    component_type entity::get_component_mask() const
    {
        return m_component_mask;
    }

    void entity::update_on_tick()
    {
        m_update_on_tick = true;
    }
}
