/// @file node.cpp

#include <assert.h>
#include <limits.h>
#include <math.h>
#include "plog/Log.h"
#include "node.hpp"

namespace ui
{
    void node::initialise()
    {
        on_initialise();

        for (auto& p_child : m_children)
        {
            p_child->initialise();
        }
    }

    void node::load(core::resource_manager* p_resource_manager)
    {
        on_load(p_resource_manager);

        for (auto& p_child : m_children)
        {
            p_child->load(p_resource_manager);
        }
    }

    void node::layout()
    {
        if (m_invalid)
        {
            on_layout();

            if (m_h_layout_mode == layout_mode::align)
            {
                align_horizontal();
            }

            if (m_v_layout_mode == layout_mode::align)
            {
                align_vertical();
            }

            m_invalid = false;
        }

        for (auto& p_child : m_children)
        {
            p_child->layout();
        }
    }

    void node::measure()
    {
        if (mp_parent != nullptr)
        {
            if (m_h_measure_mode == measure_mode::inflate)
            {
                m_width = mp_parent->get_width() - (mp_parent->get_padding_x() * 2.0f);
            }

            if (m_v_measure_mode == measure_mode::inflate)
            {
                m_height = mp_parent->get_height() - (mp_parent->get_padding_y() * 2.0f);
            }
        }

        for (auto& p_child : m_children)
        {
            p_child->measure();
        }
    }

    void node::draw(core::draw_manager* p_draw_manager)
    {
        // Debug draw borders around nodes
        // auto x = get_world_x();
        // auto y = get_world_y();
        // auto w = width;
        // auto h = height;
        // auto color = render::color(255, 255, 255, 255);
        // p_draw_manager->render_draw_line(x, y, x + w, y, color);
        // p_draw_manager->render_draw_line(x + w, y, x + w, y + h, color);
        // p_draw_manager->render_draw_line(x, y + h, x + w, y + h, color);
        // p_draw_manager->render_draw_line(x, y + h, x, y, color);

        on_draw(p_draw_manager);

        for (auto& p_child : m_children)
        {
            p_child->draw(p_draw_manager);
        }
    }

    void node::add_child(std::unique_ptr<node> p_node)
    {
        p_node->set_parent(this);
        m_children.push_back(std::move(p_node));
    }

    void node::invalidate()
    {
        m_invalid = true;

        for (auto& p_child : m_children)
        {
            p_child->invalidate();
        }
    }

    void node::set_x(float x)
    {
        m_x = x;
        m_h_layout_mode = layout_mode::fixed;

        invalidate();
    }

    void node::set_y(float y)
    {
        m_y = y;
        m_v_layout_mode = layout_mode::fixed;

        invalidate();
    }

    float node::get_world_x() const
    {
        float world_x{m_x};
        if (mp_parent != nullptr)
        {
            world_x += mp_parent->get_world_x();
        }
        return world_x;
    }

    float node::get_world_y() const
    {
        float world_y{m_y};
        if (mp_parent != nullptr)
        {
            world_y += mp_parent->get_world_y();
        }
        return world_y;
    }

    void node::set_width(float width)
    {
        m_width = width;
        m_h_measure_mode = measure_mode::fixed;

        invalidate();
    }

    void node::set_height(float height)
    {
        m_height = height;
        m_v_measure_mode = measure_mode::fixed;

        invalidate();
    }

    void node::set_min_width(float min_width)
    {
        m_min_width = min_width;
    }

    void node::set_min_height(float min_height)
    {
        m_min_height = min_height;
    }

    void node::set_max_width(float max_width)
    {
        m_max_width = max_width;
    }

    void node::set_max_height(float max_height)
    {
        m_max_height = max_height;
    }

    void node::set_padding_x(float padding)
    {
        m_padding_x = padding;

        invalidate();
    }

    float node::get_padding_x() const
    {
        return m_padding_x;
    }

    void node::set_padding_y(float padding)
    {
        m_padding_y = padding;

        invalidate();
    }

    float node::get_padding_y() const
    {
        return m_padding_y;
    }

    void node::set_margin_x(float margin)
    {
        m_margin_x = margin;

        invalidate();
    }

    void node::set_margin_y(float margin)
    {
        m_margin_y = margin;

        invalidate();
    }

    float node::get_width() const
    {
        return m_width;
    }

    float node::get_height() const
    {
        return m_height;
    }

    void node::set_horizontal_alignment(horizontal_alignment alignment)
    {
        m_h_align = alignment;
    }

    void node::set_vertical_alignment(vertical_alignment alignment)
    {
        m_v_align = alignment;
    }

    void node::set_focusable(bool focusable)
    {
        m_focusable = focusable;
    }

    void node::focused()
    {
        m_focused = true;
        on_focus();
    }

    void node::unfocused()
    {
        m_focused = false;
        on_focus_lost();
    }

    bool node::is_focused() const
    {
        return m_focused;
    }

    void node::set_parent(node* p_node)
    {
        if (mp_parent != nullptr)
        {
            PLOG_ERROR << "Node can only have one parent";
            assert(false);
        }

        mp_parent = p_node;
    }

    void node::align_horizontal()
    {
        m_x = (mp_parent == nullptr) ?
              calculate_alignment(m_width, 0.0f, m_h_align, 0.0f, m_margin_x) :
              calculate_alignment(m_width, mp_parent->get_width(), m_h_align, mp_parent->get_padding_x(), m_margin_x);
    }

    void node::align_vertical()
    {
        m_y = (mp_parent == nullptr) ?
              calculate_alignment(m_height, 0.0f, m_v_align, 0.0f, m_margin_y) :
              calculate_alignment(m_height, mp_parent->get_height(), m_v_align, mp_parent->get_padding_y(), m_margin_y);
    }

    node* node::get_node_at(float x, float y)
    {
        const auto world_pos_x = get_world_x();
        const auto world_pos_y = get_world_y();
        if (x > world_pos_x && x < world_pos_x + m_width &&
            y > world_pos_y && y < world_pos_y + m_height)
        {
            for (auto& it : m_children)
            {
                node* p_node = it->get_node_at(x, y);
                if (p_node != nullptr)
                {
                    return p_node;
                }
            }

            return this;
        }

        return nullptr;
    }

    node* node::get_focusable_node_at(float x, float y)
    {
        if (m_focusable)
        {
            const auto world_pos_x = get_world_x();
            const auto world_pos_y = get_world_y();
            if (x > world_pos_x && x < world_pos_x + m_width &&
                y > world_pos_y && y < world_pos_y + m_height)
            {
                for (auto& it : m_children)
                {
                    node* p_node = it->get_focusable_node_at(x, y);
                    if (p_node != nullptr)
                    {
                        return p_node;
                    }
                }

                return this;
            }
        }

        return nullptr;
    }

    float node::calculate_alignment(float x1, float x2, horizontal_alignment alignment, float padding, float margin)
    {
        switch (alignment)
        {
            case horizontal_alignment::left:
                return padding + margin;
            case horizontal_alignment::right:
                return x2 - x1 - padding - margin;
            case horizontal_alignment::centre:
                return static_cast<float>(round((x2 - x1) / 2.0));
            default:
                PLOG_ERROR << "Unknown alignment value " << std::to_string(static_cast<int>(alignment));
                break;
        }

        return 0;
    }

    float node::calculate_alignment(float y1, float y2, vertical_alignment alignment, float padding, float margin)
    {
        switch (alignment)
        {
            case vertical_alignment::top:
                return padding + margin;
            case vertical_alignment::bottom:
                return y2 - y1 - padding - margin;
            case vertical_alignment::centre:
                return static_cast<float>(round((y2 - y1) / 2.0));
            default:
                PLOG_ERROR << "Unknown alignment value " << std::to_string(static_cast<int>(alignment));
                break;
        }

        return 0;
    }
} /// namespace ui
