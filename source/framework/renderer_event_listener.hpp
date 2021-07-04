/// @file renderer_event_listener.hpp

#ifndef RENDERER_EVENT_LISTENER_HPP
#define RENDERER_EVENT_LISTENER_HPP


/// @namespace framework namespace
namespace framework
{

    /// @brief Interface that can be registered with a renderer, providing ability to implement responses to display
    /// events
    class renderer_event_listener
    {
        public:
        /// @brief Display close event handler
        virtual void on_display_close() = 0;
    };
}

#endif /// RENDERER_EVENT_LISTENER_HPP
