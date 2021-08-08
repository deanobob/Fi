/// @file movement_component.hpp
/// @brief The movement component

#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The movement component
    class movement_component
        : public component
    {
        public:
        /// @brief Construct a new movement component object
        /// @param velocity The initial velocity in pixels per second
        movement_component(float velocity = 0.0f)
            : m_velocity{velocity}
        {

        }

        /// @brief Get the movement component type
        /// @return The movement component type
        component_type get_type() const override
        {
            return component_type::movement;
        }

        /// @brief Set the velocity of the entity in pixels per second
        /// @param velocity The velocity in pixels per second
        void set_velocity(float velocity)
        {
            m_velocity = velocity;
        }

        /// @brief Get the velocity in pixels per second
        /// @return The velocity in pixels per second
        float get_velocity() const
        {
            return m_velocity;
        }

        private:
        /// @brief The velocity in pixels per second
        float m_velocity{};
    };
} /// namespace core

#endif /// MOVEMENT_COMPONENT_HPP
