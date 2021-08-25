/// @file track_edit_window.hpp

#ifndef TRACK_EDIT_WINDOW_HPP
#define TRACK_EDIT_WINDOW_HPP

#include "node.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The root of a basic track_edit_window UI element
    /// @details Contains and manages child elements
    class track_edit_window
        : public node
    {
        public:
        /// @brief Construct a new track editor window
        /// @param p_message_bus The message bus
        track_edit_window(core::message_bus* p_message_bus);
        /// @brief Destroy the track edit window object
        virtual ~track_edit_window() = default;

        protected:
        void on_initialise() override;

        void on_layout() override;

        void on_draw(core::draw_manager* p_draw_manager) override;

        private:
        /// @brief The message bus
        core::message_bus* mp_message_bus{nullptr};
    };
} /// namespace ui

#endif /// TRACK_EDIT_WINDOW_HPP
