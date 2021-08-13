/// @file movement_component.hpp
/// @brief The movement component

#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP

#include <math.h>
#include "component.hpp"
#include "component_type.hpp"
#include "vector2.hpp"

/// @namespace core namespace
namespace core
{

    class path
    {
        public:
        virtual ~path() = default;

        virtual const utilities::vector2 get_position(double distance_travelled) const = 0;

        virtual double get_distance() const = 0;
    };

    class straight_path : public path
    {
        public:
        straight_path(const utilities::vector2& start, const utilities::vector2& end)
            : m_start{start}
            , m_end{end}
            , m_distance{utilities::vector2::distance(m_start, m_end)}
        {

        }

        const utilities::vector2 get_position(double distance_travelled) const override
        {
            const auto percentage_travelled {(1.0f / m_distance) * distance_travelled};
            
            return utilities::vector2::lerp(m_start, m_end, static_cast<float>(percentage_travelled));
        }

        double get_distance() const override
        {
            return m_distance;
        }

        private:
        const utilities::vector2 m_start;
        const utilities::vector2 m_end;
        const double m_distance;
    };
    
    class curved_path_clockwise : public path
    {
        public:
        curved_path_clockwise(const utilities::vector2& start, float radius, float angle, float start_angle = 0.0f)
            : m_start{start}
            , m_radius{radius}
            , m_start_angle{start_angle}
            , m_angle{angle}
            , m_centre{m_start + utilities::vector2::forward(utilities::math::to_radians(start_angle)) * radius}
            , m_distance{(m_angle / 360.f) * M_PI * (m_radius * 2.0)}
        {
            LOG_DEBUG << "Distance: " << m_distance;
            LOG_DEBUG << "Centre: " << m_centre.x << ", " << m_centre.y;
        }

        const utilities::vector2 get_position(double distance_travelled) const override
        {
            // const auto angle_travelled {m_angle - (m_angle / m_distance) * distance_travelled};
            const auto angle_travelled {(m_angle / m_distance) * distance_travelled};
            return utilities::vector2{
                static_cast<float>(m_centre.x + m_radius * cos(utilities::math::to_radians(m_start_angle + angle_travelled - 180.f))), 
                static_cast<float>(m_centre.y + m_radius * sin(utilities::math::to_radians(m_start_angle + angle_travelled - 180.f)))};
        }

        double get_distance() const override
        {
            return m_distance;
        }

        private:
        const utilities::vector2 m_start;
        const float m_radius;
        const float m_start_angle;
        const float m_angle;
        const utilities::vector2 m_centre;
        const double m_distance;
    };

    class curved_path_anti_clockwise : public path
    {
        public:
        curved_path_anti_clockwise(const utilities::vector2& start, float radius, float angle, float start_angle = 0.0f)
            : m_start{start}
            , m_radius{radius}
            , m_start_angle{start_angle}
            , m_angle{angle}
            , m_centre{m_start - utilities::vector2::forward(utilities::math::to_radians(start_angle)) * radius}
            , m_distance{(m_angle / 360.f) * M_PI * (m_radius * 2.0)}
        {
            LOG_DEBUG << "Distance: " << m_distance;
            LOG_DEBUG << "Centre: " << m_centre.x << ", " << m_centre.y;
        }

        const utilities::vector2 get_position(double distance_travelled) const override
        {
            const auto angle_travelled {m_angle - (m_angle / m_distance) * distance_travelled};
            return utilities::vector2{
                static_cast<float>(m_centre.x + m_radius * cos(utilities::math::to_radians(m_start_angle + angle_travelled - m_angle))), 
                static_cast<float>(m_centre.y + m_radius * sin(utilities::math::to_radians(m_start_angle + angle_travelled - m_angle)))};
        }

        double get_distance() const override
        {
            return m_distance;
        }

        private:
        const utilities::vector2 m_start;
        const float m_radius;
        const float m_start_angle;
        const float m_angle;
        const utilities::vector2 m_centre;
        const double m_distance;
    };

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
            // m_route.push_back(std::make_unique<straight_path>(utilities::vector2{5000, 5000}, utilities::vector2{5000, 5500}));
            // m_route.push_back(std::make_unique<straight_path>(utilities::vector2{5000, 5500}, utilities::vector2{6500, 5500}));
            // m_route.push_back(std::make_unique<straight_path>(utilities::vector2{6500, 5500}, utilities::vector2{3000, 3000}));
            m_route.push_back(std::make_unique<straight_path>(utilities::vector2{4000, 5000}, utilities::vector2{5000, 5000}));
            m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{5000, 5000}, 200, 180, 90));
            // m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{5200, 5200}, 200, 90, 180));
            m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{5000, 5400}, 200, 90, 270));
            m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{4800, 5200}, 200, 90));
            // m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{5000, 5000}, 200, 90, 90));
            // m_route.push_back(std::make_unique<curved_path_clockwise>(utilities::vector2{5200, 5200}, 200, 90, 180));
            //m_route.push_back(std::make_unique<straight_path>(utilities::vector2{5000, 5400}, utilities::vector2{4000, 5400}));
            m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{5000, 5000}, 200, 180, 90));
            // m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{5200, 4800}, 200, 90));
            m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{5000, 4600}, 200, 90, 270));
            m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{4800, 4800}, 200, 90, 180));
            // m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{5000, 5000}, 200, 90, 90));
            // m_route.push_back(std::make_unique<curved_path_anti_clockwise>(utilities::vector2{5200, 4800}, 200, 90));
            m_route.push_back(std::make_unique<straight_path>(utilities::vector2{5000, 5000}, utilities::vector2{6000, 5000}));
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

        const std::list<std::unique_ptr<core::path> >& get_path() const
        {
            return m_route;
        }

        private:
        /// @brief The velocity in pixels per second
        float m_velocity{};

        std::list<std::unique_ptr<core::path> > m_route{};
    };
} /// namespace core

#endif /// MOVEMENT_COMPONENT_HPP
