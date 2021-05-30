/// @file console.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "console.hpp"

namespace services
{
    console::console(core::game* p_game):
        service(p_game)
    {

    }

    void console::read_input()
    {
        std::string input;
        while (m_running && std::getline(std::cin, input))
        {
            std::cout << input << std::endl;
        }
    }

    bool console::initialise()
    {
        if (m_read_thread.joinable()) m_read_thread.join();
        m_read_thread = std::thread(&console::read_input, this);

        return true;
    }

    void console::update(utilities::gametime& p_gametime)
    {

    }

    void console::shutdown()
    {
        m_running = false;
        if (m_read_thread.joinable())
        {
            m_read_thread.join();
        }
    }
}
