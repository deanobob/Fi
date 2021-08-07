/// @file entity_event_args.hpp
/// @brief Event args for events that pass an entity as an argument

#ifndef ENTITY_EVENT_ARGS_HPP
#define ENTITY_EVENT_ARGS_HPP

#include "entity.hpp"
#include "event_args.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief The event handler base class
    class entity_event_args 
        : public event_args
    {
        public:
        /// @brief Construct a new entity event args object
        /// @param p_entity The entity
        entity_event_args(entity* p_entity)
            : mp_entity{p_entity}
        {}

        /// @brief Destroy the entity event args object
        virtual ~entity_event_args() = default;
        
        /// @brief Get the entity
        /// @return The entity
        entity* get_entity() const
        {
            return mp_entity;
        }

        private:
        /// @brief The entity
        entity* mp_entity{nullptr};       
    };
} /// namespace core

#endif /// ENTITY_EVENT_ARGS_HPP