/// @file input_event_listener.hpp

#ifndef INPUT_EVENT_LISTENER_HPP
#define INPUT_EVENT_LISTENER_HPP

/// @namespace framework namespace
namespace framework
{
    /// @brief Interface that can be registered with an input, providing ability to implement responses to input events
    class input_event_listener
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

#endif /// INPUT_EVENT_LISTENER_HPP
