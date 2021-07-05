/*
 * keyboard_state.cpp
 *
 *  Created on: 1 Sep 2013
 *      Author: deano
 */

#include <algorithm>
#include "keyboard_state.hpp"

namespace services
{

keyboard_state::keyboard_state()
{

}

void keyboard_state::set_key_state(key key, bool pressed)
{
    if (pressed)
    {
        pressed_key_list.remove(key);
    }
    else
    {
        pressed_key_list.push_back(key);
    }
}

bool keyboard_state::is_key_pressed(Key key) const
{
    return std::find(pressed_key_list.begin(), pressed_key_list.end(), key) != pressed_key_list.end();
}

} /// namespace services
