/// @file physics_component.hpp
/// @brief The physics component

#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The physics component
    class physics_component
        : public component
    {
        public:
        /// @brief Construct a new physics component object
        /// @param velocity The initial velocity
        physics_component(const utilities::vector2& velocity = utilities::vector2::ZERO)
            : m_velocity{velocity}
        {
            
        }

        /// @brief Get the physics component type
        /// @return The physics component type
        component_type get_type() const override
        {
            return component_type::physics;
        }

        /// @brief Set the velocity
        /// @param velocity The new velocity
        void set_velocity(const utilities::vector2& velocity)
        {
            m_velocity = velocity;
        }

        /// @brief Get the velocity
        /// @return The velocity
        const utilities::vector2& get_velocity() const
        {
            return m_velocity;
        }

        private:
        /// @brief The velocity of the entity
        utilities::vector2 m_velocity{};
    };
} /// namespace core

#endif /// PHYSICS_COMPONENT_HPP
