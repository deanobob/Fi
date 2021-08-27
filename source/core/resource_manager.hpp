/// @file resource_manager.hpp
/// @brief The resource_manager class

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include "render_controller.hpp"

/// @namespace core namespace
namespace core
{
    /// @brief Manages loading resources and providing access to them
    class resource_manager
    {
        public:
        /// @brief Construct a new resource manager object
        /// @param p_render_controller The render controller instance
        resource_manager(render::render_controller* p_render_controller);
        /// @brief Destructor
        virtual ~resource_manager();

        /// @brief Load the game resources
        /// @return Success if all resources loaded, else failure
        bool load();

        /// @brief Get the resource_id for a given resource tag
        /// @param resource_tag The resource tag to search for
        /// @return The resource id of a resource, or -1 on failure
        render::resource_id get_resource_id(const std::string& resource_tag) const;

        private:
        /// @brief The render controller instance
        render::render_controller* mp_render_controller{nullptr};
        /// @brief Loaded image resources identifiers mapped to string identifiers
        std::map<const std::string, render::resource_id> m_image_tag_resource_id_map;

        /// @brief Loads as sub-bitmap from an image resource into the resource manager
        /// @param resource_tag Unique string that allows access to the sub-bitmap resource
        /// @param filename The image filename
        /// @param position The start position of the sub-bitmap 
        /// @param size The size of the sub-bitmap
        /// @return True on success, false if failed to load
        bool load_bitmap(const std::string& resource_tag,
                         const std::string& filename, 
                         const utilities::vector2& position,
                         const utilities::vector2& size);

    };
} /// namespace core

#endif /// RESOURCE_MANAGER_HPP
