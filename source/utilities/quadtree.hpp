/// @file quadtree.hpp
/// @brief Implementation of a quadtree

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <list>
#include <map>
#include <memory>
#include <string>
#include "rectangle.hpp"

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Structure that defines a leaf node in the quadtree
    struct leaf
    {
        /// @brief The entity identifier
        const unsigned int m_id;
        /// @brief The boundary of the leaf node
        const rectangle m_boundary;
        
        /// @brief Construct a new leaf object
        /// @param id The leaf identifier
        /// @param bounds The boundary of the leaf node
        leaf(unsigned int id, const rectangle& boundary) :
            m_id(id), m_boundary(boundary)
        {}
    };

    /// @brief implementation of a quadtree data structure 
    class quadtree
    {
        public:
        /// @brief Construct a new quadtree object
        /// @param boundary The boundary of the quadtree 
        /// @param p_parent Pointer to the parent quadtree object
        quadtree(rectangle boundary, quadtree* p_parent = nullptr);

        /// @brief Insert an entity location into the quadtree, keyed by entity ID 
        /// @param entity_id The entity identifier
        /// @param rectangle The boundary of the entity body
        /// @return True if successfully inserted, false if failed to insert
        bool insert(unsigned int entity_id, const rectangle& rectangle);

        /// @brief Query the quadtree for all elements within a given region 
        /// 
        /// @param region The region to query
        /// @return The entity IDs of all entities within the given region
        std::list<unsigned int> query(const rectangle& region);

        /// @brief Remove the entity from the quadtree
        bool remove(unsigned int entity_id);

        /// @brief Convert the quadtree state into a human readable string
        /// @details For debugging 
        /// @param indent The indent string appended to the beginning of each line 
        void to_string(const std::string& indent) const;

        private:
        /// @brief Map that links an entity ID to the quadtree object it is assigned to
        std::map<unsigned int, quadtree*> m_leaf_location_map{};
        /// @brief Container of all child leave objects
        std::list<leaf> m_leaf_list{};
        /// @brief The parent quadtree object
        quadtree* mp_parent{nullptr};
        /// @brief The north west child quadtree
        std::unique_ptr<quadtree> mp_north_west{nullptr};
        /// @brief The north east child quadtree
        std::unique_ptr<quadtree> mp_north_east{nullptr};
        /// @brief The south west child quadtree
        std::unique_ptr<quadtree> mp_south_west{nullptr};
        /// @brief The south east child quadtree
        std::unique_ptr<quadtree> mp_south_east{nullptr};
        /// @brief The quadtree boundary
        const rectangle m_boundary;

        /// @brief Divide the quadtree into four child nodes and distribute the objects contained within the node 
        void subdivide();

        /// @brief Get the quadtree that contains the given entity ID
        /// @param entity_id The entity ID
        /// @return The quadtree that contains the given entity ID
        quadtree* get_location(unsigned int entity_id) const;

        /// @brief Set the quadtree that contains the object
        /// @param entity_id The entity ID
        /// @param p_quadtree Pointer to the quadtree object
        void set_location(unsigned int entity_id, quadtree* p_quadtree);

        /// @brief Erase an entity from the quadtree object 
        /// @param entityId The identifier of the entity to remove
        /// @return True on success, else false
        bool erase(unsigned int entity_id);
    };
} /// namespace utilities

#endif /// QUADTREE_HPP
