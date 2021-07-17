/// @file window.hpp

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "node.hpp"

namespace ui
{
    class window
        : public node
    {
        public:
        window() = default;
        virtual ~window() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        void on_mouse_axis_changed(int position_x, int position_y, int position_z) override;
    };
} /// namespace ui

#endif /// WINDOW_HPP
