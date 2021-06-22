/// @file entity.hpp
/// @brief Entity base class

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <list>
#include <map>
#include <memory>
#include <stdlib.h>
#include "component.hpp"
#include "component_type.hpp"
#include "gametime.hpp"
#include "publisher.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Alias for entity ID
    using entity_id = uint32_t;

    /// @brief The base entity class
    class entity
    {
        public:
        /// @brief Constructor
        /// @param tag The entity tag
        entity(std::string tag = "");
        /// @brief Default destructor
        virtual ~entity() = default;

        /// @brief Method that is called on every tick, providing the entity with the elapsed and total gametime
        /// @details Calls on_update function if m_update_on_tick is set to true
        /// @param gametime The game time object
        void update(utilities::gametime& gametime);

        /// @brief Add component to entity
        /// @param component The component to add to the entity
        /// @return True if added, false if entity ID doesn't exist
        bool add_component(std::unique_ptr<component> component);

        /// @brief Remove component from entity
        /// @param type The component type to remove from the entity
        /// @return True if removed, false on failure
        bool remove_component(component_type type);

        /// @brief Get the component of the given type, cast to the template type
        /// @note Defined in header due to non-specialized template
        /// @param type The component type
        /// @return The component reference cast to template type T or nullptr
        template <typename T>
        T* get_component(component_type type)
        {
            const auto& component_iter = m_components.find(type);
            if (component_iter == m_components.end())
            {
                // Component of given type doesn't exist
                return nullptr;
            }

            return dynamic_cast<T*>(component_iter->second.get());
        };

        /// @brief Get the entity ID
        /// @return Returns the entity ID
        entity_id get_id() const;

        /// @brief Gets the entity tag
        /// @return The entity tag
        const std::string& get_tag() const;

        /// @brief Gets the component mask
        /// @return The component mask
        component_type get_component_mask() const;

        /// @brief Configure the entity to update on tick
        void update_on_tick();

        protected:
        /// @brief Pure virtual method allowing derived classes to handle update method calls
        /// @param gametime The game time object
        virtual void on_update(utilities::gametime& gametime) {};

        private:
        /// @brief Contains the next available entity ID
        static entity_id next_entity_id;
        /// @brief The entity ID
        const entity_id m_id;
        /// @brief A string identifier for the entity
        const std::string m_tag;
        /// @brief A map containing the components that form the entity
        std::map<component_type, std::unique_ptr<component> > m_components{};
        /// @brief The component mask
        component_type m_component_mask{component_type::none};
        /// @brief Flag defining if the entity update function is called on every tick
        bool m_update_on_tick{false};
    };
} /// namespace core

#endif /// ENTITY_HPP
