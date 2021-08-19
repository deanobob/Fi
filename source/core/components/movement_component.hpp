/// @file movement_component.hpp
/// @brief The movement component

#ifndef MOVEMENT_COMPONENT_HPP
#define MOVEMENT_COMPONENT_HPP

#include <math.h>
#include "component.hpp"
#include "component_type.hpp"
#include "path_segment.hpp"
#include "path_segment_curved.hpp"
#include "path_segment_straight.hpp"
#include "vector2.hpp"

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
            auto seg1 = std::make_unique<path_segment_straight>(utilities::vector2{4500, 5015}, 0.f, 1000);
            auto seg2 = std::make_unique<path_segment_curved>(seg1->get_end_position(), 200, 180, seg1->get_end_rotation(), true);
            auto seg3 = std::make_unique<path_segment_straight>(seg2->get_end_position(), seg2->get_end_rotation(), 1000);
            auto seg4 = std::make_unique<path_segment_curved>(seg3->get_end_position(), 200, 180, seg3->get_end_rotation(), true);
            auto seg5 = std::make_unique<path_segment_straight>(seg4->get_end_position(), seg4->get_end_rotation(), 200);
            auto seg6 = std::make_unique<path_segment_curved>(seg5->get_end_position(), 200, 45, seg5->get_end_rotation(), true);
            auto seg7 = std::make_unique<path_segment_straight>(seg6->get_end_position(), seg6->get_end_rotation(), 200);
            auto seg8 = std::make_unique<path_segment_curved>(seg7->get_end_position(), 200, 45, seg7->get_end_rotation(), false);
            auto seg9 = std::make_unique<path_segment_straight>(seg8->get_end_position(), seg8->get_end_rotation(), 1000);
            m_route.push_back(std::move(seg1));
            m_route.push_back(std::move(seg2));
            m_route.push_back(std::move(seg3));
            m_route.push_back(std::move(seg4));
            m_route.push_back(std::move(seg5));
            m_route.push_back(std::move(seg6));
            m_route.push_back(std::move(seg7));
            m_route.push_back(std::move(seg8));
            m_route.push_back(std::move(seg9));
            
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

        const std::list<std::unique_ptr<core::path_segment> >& get_path() const
        {
            return m_route;
        }

        private:
        /// @brief The velocity in pixels per second
        float m_velocity{};

        std::list<std::unique_ptr<core::path_segment> > m_route{};
    };
} /// namespace core

#endif /// MOVEMENT_COMPONENT_HPP
