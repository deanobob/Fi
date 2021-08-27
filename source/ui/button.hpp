/// @file button.hpp

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "node.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic button UI element
    class button
        : public node
    {
        public:
        /// @brief Construct a new button object
        button() = default;
        /// @brief Destroy the button object
        virtual ~button() = default;

        /// @brief Set the icon resource tag
        /// @param icon_tag The icon resource tag
        void set_icon(const std::string& icon_tag);

        protected:
        void on_initialise() override;

        void on_load(core::resource_manager* p_resource_manager) override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void mouse_button_pressed(const input::mouse_button mouse_button, int position_x, int position_y) override;

        void mouse_button_released(const input::mouse_button mouse_button, int position_x, int position_y) override;

        /// @brief Called when button is pressed
        virtual void on_press() = 0;

        /// @brief Called when button is released
        virtual void on_release() = 0;

        private:
        /// @brief The icon resource tag
        std::string m_icon_tag{""};
        /// @brief The icon resource id
        render::resource_id m_resource_id{render::resource_id_unknown};
    };
} /// namespace ui

#endif /// BUTTON_HPP
