/// @file quadtree.cpp

#include "plog/Log.h"
#include "quadtree.hpp"

namespace utilities
{
    /// @brief The maximum capacity of a quadtree node before it is subdivided
    static constexpr int CAPACITY = 4;

    quadtree::quadtree(rectangle boundary, quadtree* mp_parent) 
        : mp_parent(mp_parent)
        , m_boundary(boundary)
    {
    
    }

    bool quadtree::insert(unsigned int id, const rectangle& rectangle)
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
                rc = mp_north_west->insert(id, rectangle) ||
                    mp_north_east->insert(id, rectangle) ||
                    mp_south_west->insert(id, rectangle) ||
                    mp_south_east->insert(id, rectangle);
            }

            if (!rc)
            {
                m_leaf_list.push_back({id, rectangle});
                set_location(id, this);
                rc = true;
            }
        }

        return rc;
    }

    std::list<unsigned int> quadtree::query(const rectangle& rectangle)
    {
    std::list<unsigned int> result{};

    if (m_boundary.intersects(rectangle))
    {
        for (const auto& leaf : m_leaf_list)
        {
            if (leaf.m_boundary.intersects(rectangle))
            {
                result.push_back(leaf.m_id);
            }
        }

        if (mp_north_east != nullptr)
        {
            result.splice(result.end(), mp_north_east->query(rectangle));
            result.splice(result.end(), mp_north_west->query(rectangle));
            result.splice(result.end(), mp_south_east->query(rectangle));
            result.splice(result.end(), mp_south_west->query(rectangle));
        }
    }

    return result;
    }

    bool quadtree::remove(unsigned int entity_id)
    {
        auto rc{false};

        quadtree* p_quadtree = get_location(entity_id);
        if (p_quadtree != nullptr)
        {
            rc = p_quadtree->erase(entity_id);
        }

        return rc;
    }

    void quadtree::to_string(const std::string& indent) const
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

    void quadtree::subdivide()
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

        std::list<leaf> leaves = m_leaf_list;
        m_leaf_list.clear();

        for (const auto& leaf : leaves)
        {
            insert(leaf.m_id, leaf.m_boundary);
        }
    }

    quadtree* quadtree::get_location(unsigned int entity_id) const
    {
        quadtree* p_quadtree{nullptr};

        if (mp_parent == nullptr)
        {
            std::map<unsigned int, quadtree*>::const_iterator it = m_leaf_location_map.find(entity_id);
            if (it != m_leaf_location_map.end())
            {
                p_quadtree = (*it).second;
            }
            else
            {
                PLOG_DEBUG << "Unknown entity ID: " << entity_id;
            }
        }
        else
        {
            mp_parent->get_location(entity_id);
        }

        return p_quadtree;
    }

    void quadtree::set_location(unsigned int entity_id, quadtree* p_quadtree)
    {
        if (mp_parent == nullptr)
        {
            if (p_quadtree == nullptr)
            {
                m_leaf_location_map.erase(entity_id);
            }
            else
            {
                m_leaf_location_map[entity_id] = p_quadtree;
            }
        }
        else
        {
            mp_parent->set_location(entity_id, p_quadtree);
        }
    }

    bool quadtree::erase(unsigned int entity_id)
    {
        bool rc{false};

        for (std::list<leaf>::iterator it = m_leaf_list.begin();
            it != m_leaf_list.end();
            ++it)
        {
            auto leaf = (*it);
            
            if (leaf.m_id == entity_id)
            {
                m_leaf_list.erase(it);
                set_location(entity_id, nullptr);
                rc = true;
                break;
            }
        }

        return rc;
    }
} /// namespace utilities
