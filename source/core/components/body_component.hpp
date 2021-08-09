/// @file body_component.hpp
/// @brief The body component

#ifndef BODY_COMPONENT_HPP
#define BODY_COMPONENT_HPP

#include "component.hpp"
#include "component_type.hpp"
#include "math.hpp"
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
        /// @param rotation The rotation of the body in degrees
        body_component(const utilities::vector2& position, const utilities::vector2& size, double rotation = 0.0);

        /// @brief Get the body component type
        /// @return The body component type
        component_type get_type() const override
        {
            return component_type::body;
        }

        /// @brief Get the body coordinates
        /// @return The body location coordinates as a vector
        const utilities::vector2& get_position() const;

        /// @brief Get the body coordinates adjusted by delta fast-forwarding to allow for fraction of a frame
        /// @param delta The fraction of a frame value
        /// @return The body location coordinates as a vector
        const utilities::vector2 get_interpolated_position(double delta) const;

        /// @brief Hard set of the position of the entity, also overwriting the previous position value to avoid
        /// interpolating large distances. Use 'move' to incrementally adjust location, allowing interpolation
        /// of position between frames.
        /// @param position The new position
        void set_position(const utilities::vector2& position);

        /// @brief Rotate the body the given value
        /// @param value The amount to rotate by
        /// @param unit The unit type (degrees / radians), defaults to degrees
        void rotate(double value, utilities::math::unit_type unit = utilities::math::unit_type::degrees);

        /// @brief Set the body rotation
        /// @param rotation The rotation value
        /// @param unit The unit type (degrees / radians), defaults to degrees
        void set_rotation(double rotation, utilities::math::unit_type unit = utilities::math::unit_type::degrees);

        /// @brief Get the forward direction of the body
        /// @return The forward value
        utilities::vector2 forward() const;

        /// @brief Move the body by a given step
        /// @param step The step as a vector
        void move(const utilities::vector2& step);

        /// @brief Get the body width and height
        /// @return The width and height as a vector
        const utilities::vector2& get_size() const;

        private:
        /// @brief The body location coordinates (x and y)
        utilities::vector2 m_current_position{};
        /// @brief The body location coordinates (x and y)
        utilities::vector2 m_previous_position{};
        /// @brief The body size dimensions (width and height)
        utilities::vector2 m_size{};
        /// @brief The body rotation
        double m_rotation{0.0};
    };
} /// namespace core

#endif /// BODY_COMPONENT_HPP
