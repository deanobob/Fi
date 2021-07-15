/// @file body_component.hpp
/// @brief The body component

#ifndef BODY_COMPONENT_HPP
#define BODY_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"
#include "vector2.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The body component
    class body_component
        : public component
    {
        public:
        /// @brief Construct a new body component object
        /// @param position The body location coordinates (x, y)
        /// @param size The body component dimensions (width, height)
        body_component(const utilities::vector2& position, const utilities::vector2& size);

        /// @brief Get the body component type
        /// @return The body component type
        component_type get_type() const override
        {
            return component_type::body;
        }

        /// @brief Get the body coordinates //TODO: Probably should move to a different structure
        /// @return The body location coordinates as a vector
        const utilities::vector2& get_position() const;

        /// @brief Move the body by a given step
        /// @param step The step as a vector
        void move(const utilities::vector2& step);

        /// @brief Get the body width and height
        /// @return The width and height as a vector
        const utilities::vector2& get_size() const;

        private:
        /// @brief The body location coordinates (x and y)
        utilities::vector2 m_position;
        /// @brief The body size dimensions (width and height)
        utilities::vector2 m_size;
    };
} /// namespace core

#endif /// BODY_COMPONENT_HPP
