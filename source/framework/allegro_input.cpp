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
            switch (event.type)
            {
                case ALLEGRO_EVENT_KEY_DOWN:
                case ALLEGRO_EVENT_KEY_UP:
                    {
                        const auto key_code = allegro_key_to_key(event.keyboard.keycode);
                        if (key_code != services::key::unknown)
                        {
                            for (auto& listener_iter : mp_event_listeners)
                            {
                                listener_iter->on_key_state_changed(key_code, event.type == ALLEGRO_EVENT_KEY_DOWN);
                            }
                        }
                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_AXIS:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_joystick_axis_changed(0, // TODO determine joystick id
                                                                event.joystick.stick,
                                                                event.joystick.axis,
                                                                event.joystick.pos);
                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
                case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
                    {
                        for (auto& listener_iter : mp_event_listeners)
                        {
                            listener_iter->on_joystick_button_state_changed(
                                0,  // TODO determine joystick id
                                event.joystick.button,
                                event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN);
                        }
                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_mouse_button_state_changed(
                            allegro_mouse_button_to_mouse_button(event.mouse.button),
                            event.mouse.x,
                            event.mouse.y,
                            event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
                    }
                    break;
                case ALLEGRO_EVENT_MOUSE_AXES:
                    for (auto& listener_iter : mp_event_listeners)
                    {
                        listener_iter->on_mouse_axis_changed(event.mouse.x,
                                                             event.mouse.y,
                                                             event.mouse.z);
                    }
                    break;
                case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
                    PLOG_INFO << "Joystick configuration changed";
                    al_reconfigure_joysticks();
                    break;
                case ALLEGRO_EVENT_KEY_CHAR:
                    // ignore
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

    services::key allegro_input::allegro_key_to_key(unsigned int key_code)
    {
        switch (key_code)
        {
            case ALLEGRO_KEY_LEFT:
                return services::key::left;
            case ALLEGRO_KEY_RIGHT:
                return services::key::right;
            case ALLEGRO_KEY_UP:
                return services::key::up;
            case ALLEGRO_KEY_SPACE:
                return services::key::space;
            case ALLEGRO_KEY_ESCAPE:
                return services::key::escape;
            case ALLEGRO_KEY_R:
                return services::key::r;
            default:
                break;
        }

        // Return unknown key_code cast as a key to allow unsupported keys to raise events
        return static_cast<services::key>(key_code);
    }

    services::mouse_button allegro_input::allegro_mouse_button_to_mouse_button(unsigned int button_id)
    {
        switch (button_id)
        {
            case 1:
                return services::mouse_button::left;
            case 2:
                return services::mouse_button::right;
            default:
                break;
        }

        // Returns whatever the ID was, despite not knowing it explicitly.
        return static_cast<services::mouse_button>(button_id);
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
