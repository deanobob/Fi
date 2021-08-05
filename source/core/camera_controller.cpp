/// @file camera_controller.cpp

#include "plog/Log.h"
#include "camera_controller.hpp"

namespace core
{
    void camera_controller::add_camera(std::unique_ptr<camera> p_camera, const std::string& tag)
    {
        if (!tag.empty())
        {
            m_cameras_by_tag.emplace(tag, p_camera.get());
        }
        m_cameras.push_back(p_camera.get());
        m_cameras_by_id.emplace(p_camera->get_id(), std::move(p_camera));
    }

    core::camera* camera_controller::get_camera_by_id(const uint32_t camera_id) const
    {
        const auto camera_iter = m_cameras_by_id.find(camera_id);
        if (camera_iter != m_cameras_by_id.end())
        {
            return camera_iter->second.get();
        }
    }

    core::camera* camera_controller::get_camera_by_tag(const std::string& camera_tag) const
    {
        const auto camera_iter = m_cameras_by_tag.find(camera_tag);
        if (camera_iter != m_cameras_by_tag.end())
        {
            return camera_iter->second;
        }

        return nullptr;
    }

    const std::list<core::camera*>& camera_controller::get_cameras() const
    {
        return m_cameras;
    }
}
