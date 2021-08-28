/// @file label.cpp

#ifndef LABEL_HPP
#define LABEL_HPP

#include "node.hpp"
#include "text_alignment.hpp"

namespace ui
{
    /// @brief UI node used to render a text string
    class label : public node
    {
        public:
        /// @brief Constructor
        /// @param font_resource_tag The font resource tag
        label(const std::string& font_resource_tag);

        /// @brief Set the label text
        /// @param text The text to render
        void set_text(const std::string& text);

        /// @brief Set the justification
        /// @param justification The justification of the text
        void set_justification(const text_alignment justification);

        /// @brief Set the text colour
        /// @param color The colour of the text
        void set_color(const utilities::color& color);

        protected:
        void on_initialise() override;

        void on_load(core::resource_manager* p_resource_manager) override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        private:
        /// @brief The font resource tag used to access the required text
        const std::string m_font_resource_tag;

        /// @brief The unique identifier returned from the rendering engine
        /// when the font was loaded
        render::resource_id m_resource_id {render::resource_id_unknown};

        /// @brief The text string to render
        std::string m_text {""};

        /// @brief The color of the text
        utilities::color m_color {0, 0, 0};

        /// @brief The justification of the text
        text_alignment m_justification{text_alignment::left};
    };

} /* namespace ui */

#endif /* LABEL_HPP */
