/// @file camera.cpp

#include "camera.hpp"

namespace core
{
    camera::camera(const utilities::rectangle& viewport) 
        : m_viewport{viewport}
    {

    }
    
    const utilities::rectangle& camera::get_viewport() const
    {
        return m_viewport;
    }

    void camera::add_renderable(const renderable& renderable)
    {
        m_renderables.push_back(renderable);
    }

    const std::list<renderable>& camera::get_renderables() const
    {
        return m_renderables;
    }

    void camera::clear()
    {
        m_renderables.clear();
    }
}