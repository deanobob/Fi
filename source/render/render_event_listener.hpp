/// @file render_event_listener.hpp

#ifndef RENDERER_EVENT_LISTENER_HPP
#define RENDERER_EVENT_LISTENER_HPP


/// @namespace render namespace
namespace render
{
    /// @brief Interface that can be registered with a render controller, providing ability to implement responses
    /// to display events
    class render_event_listener
    {
        public:
        /// @brief Display close event handler
        virtual void on_display_close() = 0;
        /// @brief Display gained focused
        virtual void on_display_gained_focus() = 0;
        /// @brief Display lost focus
        virtual void on_display_lost_focus() = 0;
    };
}

#endif /// RENDERER_EVENT_LISTENER_HPP
