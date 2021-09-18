/// @file camera.cpp

#include <algorithm>
#include "plog/Log.h"
#include "camera.hpp"

namespace core
{
    uint32_t camera::m_next_id = 0;

    camera::camera(const utilities::vector2& position)
        : m_id{m_next_id++}
        , m_viewport{utilities::rectangle{position.x, position.y, 0, 0}}
    {

    }

    uint32_t camera::get_id() const
    {
        return m_id;
    }

    void camera::set_position(const utilities::vector2& position)
    {
        m_viewport.x = position.x - (m_viewport.width / 2.0f);
        m_viewport.y = position.y - (m_viewport.height / 2.0f);
    }

    void camera::set_dimensions(const utilities::vector2& size)
    {
        // Adjust viewport position based on difference between previous and new dimensions
        auto x_diff = m_viewport.width - size.x;
        auto y_diff = m_viewport.height - size.y;
        m_viewport.x += x_diff / 2.0f;
        m_viewport.y += y_diff / 2.0f;

        // Set the viewport dimensions
        m_viewport.width = size.x;
        m_viewport.height = size.y;
    }

    void camera::move(const utilities::vector2& offset)
    {
        m_viewport.x += offset.x;
        m_viewport.y += offset.y;
    }

    const utilities::rectangle& camera::get_viewport() const
    {
        return m_viewport;
    }

    void camera::add_renderable(std::unique_ptr<render::renderable> renderable)
    {
        m_renderables.push_back(std::move(renderable));
    }

    const std::vector<std::unique_ptr<render::renderable> >& camera::get_renderables() const
    {
        return m_renderables;
    }

    void camera::update(const utilities::gametime& p_gametime)
    {

    }

    void camera::clear()
    {
        m_renderables.clear();
    }
}
