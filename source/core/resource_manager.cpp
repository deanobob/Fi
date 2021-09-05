/// @file resource_manager.cpp

#include <memory>
#include "plog/Log.h"
#include "render_controller.hpp"
#include "resource_manager.hpp"

namespace core
{
    resource_manager::resource_manager(render::render_controller* p_render_controller)
        : mp_render_controller{p_render_controller}
    {
        assert(mp_render_controller != nullptr);
    }

    resource_manager::~resource_manager()
    {
    }

    bool resource_manager::load()
    {
        return load_bitmap("track1", "toolbar_icons.png", {0, 0}, {70, 70})
            && load_bitmap("track2", "toolbar_icons.png", {70, 0}, {70, 70})
            && load_bitmap("track3", "toolbar_icons.png", {140, 0}, {70, 70})
            && load_bitmap("track4", "toolbar_icons.png", {210, 0}, {70, 70})
            && load_bitmap("ground_1", "basic_ground_tiles.png", {128, 0}, {128, 128})
            && load_font("default_24", "roboto_regular.ttf", 24);
    }

    render::resource_id resource_manager::get_image_resource_id(const std::string& resource_tag) const
    {
        const auto iter = m_image_tag_resource_id_map.find(resource_tag);
        if (iter != m_image_tag_resource_id_map.end())
        {
            return iter->second;
        }

        return render::resource_id_unknown;
    }

    render::resource_id resource_manager::get_font_resource_id(const std::string& resource_tag) const
    {
        const auto iter = m_font_tag_resource_id_map.find(resource_tag);
        if (iter != m_font_tag_resource_id_map.end())
        {
            return iter->second;
        }

        return render::resource_id_unknown;
    }

    bool resource_manager::load_bitmap(
        const std::string& resource_tag,
        const std::string& filename,
        const utilities::vector2& position,
        const utilities::vector2& size)
    {
        LOG_DEBUG << "Loading bitmap: " << filename;

        render::resource_id res_id{0};
        if (mp_render_controller->load_bitmap(filename, position, size, res_id))
        {
            auto [iter, success] = m_image_tag_resource_id_map.try_emplace(resource_tag, res_id);
            return success;
        }

        return false;
    }

    bool resource_manager::load_font(
        const std::string& resource_tag,
        const std::string& filename,
        const uint32_t& font_size)
    {
        LOG_DEBUG << "Loading font: " << filename << " size: " << font_size;

        render::resource_id res_id{0};
        if (mp_render_controller->load_font(filename, font_size, 0, res_id))
        {
            auto [iter, success] = m_font_tag_resource_id_map.try_emplace(resource_tag, res_id);
            return success;
        }

        return false;
    }
}
