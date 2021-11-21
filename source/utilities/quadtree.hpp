/// @file quadtree.hpp
/// @brief Implementation of a quadtree

#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <list>
#include <map>
#include <memory>
#include <string>
#include "entity.hpp"
#include "rectangle.hpp"

/// @namespace utilities namespace
namespace utilities
{
    /// @brief Structure that defines a leaf node in the quadtree
    template <typename T>
    struct leaf
    {
        /// @brief The data
        const T m_data;
        /// @brief The boundary of the leaf node
        const rectangle m_boundary;

        /// @brief Construct a new leaf object
        /// @param data The leaf data
        /// @param boundary The boundary of the leaf node
        leaf(T data, const rectangle& boundary) :
            m_data(data), m_boundary(boundary)
        {}
    };

    /// @brief implementation of a quadtree data structure
    template <class T>
    class quadtree
    {
        public:
        /// @brief Construct a new quadtree object
        /// @param boundary The boundary of the quadtree
        /// @param p_parent Pointer to the parent quadtree object
        quadtree(rectangle boundary, quadtree* p_parent = nullptr)
            : mp_parent(p_parent)
            , m_boundary(boundary)
        {

        }

        /// @brief Insert data into the quadtree
        /// @param data The data
        /// @param rectangle The boundary of the data
        /// @return True if successfully inserted, false if failed to insert
        bool insert(T data, const rectangle& rectangle)
        {
            auto rc{false};
            if (m_boundary.contains(rectangle))
            {
                if (m_leaf_list.size() >= CAPACITY && mp_north_west == nullptr)
                {
                    subdivide();
                }

                if (mp_north_west != nullptr)
                {
                    rc = mp_north_west->insert(data, rectangle) ||
                        mp_north_east->insert(data, rectangle) ||
                        mp_south_west->insert(data, rectangle) ||
                        mp_south_east->insert(data, rectangle);
                }

                if (!rc)
                {
                    m_leaf_list.push_back({data, rectangle});
                    set_location(data, this);
                    rc = true;
                }
            }

            return rc;
        }

        /// @brief Query the quadtree for all elements within a given region
        ///
        /// @param region The region to query
        /// @return The data within the region
        std::list<T> query(const rectangle& region) const
        {
            std::list<T> result{};

            if (m_boundary.intersects(region))
            {
                for (const auto& leaf : m_leaf_list)
                {
                    if (leaf.m_boundary.intersects(region))
                    {
                        result.push_back(leaf.m_data);
                    }
                }

                if (mp_north_east != nullptr)
                {
                    result.splice(result.end(), mp_north_east->query(region));
                    result.splice(result.end(), mp_north_west->query(region));
                    result.splice(result.end(), mp_south_east->query(region));
                    result.splice(result.end(), mp_south_west->query(region));
                }
            }

            return result;
        }

        /// @brief Remove the data from the quadtree
        /// @param data The data to remove
        /// @return True on success, false on failure to remove
        bool remove(T data)
        {
            auto rc{false};

            quadtree* p_quadtree = get_location(data);
            if (p_quadtree != nullptr)
            {
                rc = p_quadtree->erase(data);
            }

            return rc;
        }

        /// @brief Convert the quadtree state into a human readable string
        /// @details For debugging
        /// @param indent The indent string appended to the beginning of each line
        void to_string(const std::string& indent) const
        {
            auto str = indent;

            str.append("[");
            for (const auto& leaf : m_leaf_list)
            {
                str.append(std::to_string(leaf.m_id));
                str.append(", ");
            }
            str.append("]");

            LOG_DEBUG << str;

            if (mp_north_west != nullptr)
            {
                auto new_indent{indent};
                new_indent.append("  ");
                mp_north_west->to_string(new_indent);
                mp_north_east->to_string(new_indent);
                mp_south_west->to_string(new_indent);
                mp_south_east->to_string(new_indent);
            }
        }

        private:
        /// @brief The maximum capacity of a quadtree node before it is subdivided
        static constexpr int CAPACITY = 4;

        /// @brief Map that links data to the quadtree object it is assigned to
        std::map<T, quadtree<T>*> m_leaf_location_map{};
        /// @brief Container of all child leaf objects
        std::list<leaf<T> > m_leaf_list{};
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
        void subdivide()
        {
            auto left{m_boundary.x};
            auto top{m_boundary.y};
            auto half_width{m_boundary.width / 2.0f};
            auto half_height{m_boundary.height / 2.0f};
            auto center_x{left + half_width};
            auto center_y{top + half_height};

            mp_north_west = std::make_unique<quadtree>(rectangle{left, top, half_width, half_height}, this);
            mp_north_east = std::make_unique<quadtree>(rectangle{left, top, half_width, half_height}, this);
            mp_south_west = std::make_unique<quadtree>(rectangle{center_x, center_y, half_width, half_height}, this);
            mp_south_east = std::make_unique<quadtree>(rectangle{center_x, center_y, half_width, half_height}, this);

            std::list<leaf<T>> leaves = m_leaf_list;
            m_leaf_list.clear();

            for (const auto& leaf : leaves)
            {
                insert(leaf.m_data, leaf.m_boundary);
            }
        }

        /// @brief Get the quadtree that contains the given data
        /// @param data The data
        /// @return The quadtree that contains the given data
        quadtree* get_location(T data) const
        {
            quadtree* p_quadtree{nullptr};

            if (mp_parent == nullptr)
            {
                const auto& it = m_leaf_location_map.find(data);
                if (it != m_leaf_location_map.end())
                {
                    p_quadtree = (*it).second;
                }
                else
                {
                    PLOG_DEBUG << "Unknown entity";
                }
            }
            else
            {
                mp_parent->get_location(data);
            }

            return p_quadtree;
        }

        /// @brief Set the quadtree that contains the object
        /// @param data The data
        /// @param p_quadtree Pointer to the quadtree object
        void set_location(T data, quadtree* p_quadtree)
        {
            if (mp_parent == nullptr)
            {
                if (p_quadtree == nullptr)
                {
                    m_leaf_location_map.erase(data);
                }
                else
                {
                    m_leaf_location_map[data] = p_quadtree;
                }
            }
            else
            {
                mp_parent->set_location(data, p_quadtree);
            }
        }

        /// @brief Erase data from the quadtree object
        /// @param data The identifier of the data to remove
        /// @return True on success, else false
        bool erase(T data)
        {
            bool rc{false};

            for (auto it = m_leaf_list.begin();
                it != m_leaf_list.end();
                ++it)
            {
                const auto leaf = (*it);

                if (leaf.m_data == data)
                {
                    m_leaf_list.erase(it);
                    set_location(data, nullptr);
                    rc = true;
                    break;
                }
            }

            return rc;
        }
    };
} /// namespace utilities

#endif /// QUADTREE_HPP
