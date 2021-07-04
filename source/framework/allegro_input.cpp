/// @file allegro_input.cpp

#ifndef CI

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"
#include "plog/Log.h"
#include "allegro_input.hpp"

namespace framework
{
    allegro_input::allegro_input(ALLEGRO_EVENT_QUEUE* p_event_queue)
        : mp_event_queue(p_event_queue)
    {
        al_init();

        mp_event_queue = p_event_queue ? p_event_queue : al_create_event_queue();
    }

    bool allegro_input::initialise()
    {
        bool rc = true;

        if (!al_install_mouse())
        {
            PLOG_ERROR << "Failed to install mouse";
            rc = false;
        }

        if (!al_install_keyboard())
        {
            PLOG_ERROR << "Failed to install keyboard";
            rc = false;
        }

        if (!al_install_joystick())
        {
            PLOG_ERROR << "Failed to install joystick";
            rc = false;
        }

        al_register_event_source(mp_event_queue, al_get_mouse_event_source());
        al_register_event_source(mp_event_queue, al_get_keyboard_event_source());
        al_register_event_source(mp_event_queue, al_get_joystick_event_source());

        return rc;
    }

    void allegro_input::process_events()
    {
        ALLEGRO_EVENT event;

        while (al_get_next_event(mp_event_queue, &event))
        {
            PLOG_DEBUG << "Input event type: " << event.type;
            switch (event.type)
            {
                case ALLEGRO_EVENT_KEY_DOWN:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_KEY_UP:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_AXIS:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_AXES:
                    for (auto& listener_iter : mp_event_listeners)
                    {

                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        al_reconfigure_joysticks();
                    }
                    break;
                default:
                    PLOG_DEBUG << "Unknown event" << event.type;
                    break;
            }
        }
    }

    void allegro_input::shutdown()
    {
        if (mp_event_queue)
        {
           al_destroy_event_queue(mp_event_queue);
        }
    }
} /// namespace framework

#else

#include "plog/Log.h"
#include "allegro_input.hpp"

namespace framework
{
    bool allegro_input::initialise()
    {
        return true;
    }

    void allegro_input::process_events()
    {

    }

    void allegro_input::shutdown()
    {

    }
}

#endif
