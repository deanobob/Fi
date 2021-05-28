/// @file game.cpp

#include "game.hpp"
#include "time.hpp"

namespace core
{
    void game::run()
    {
        if (initialise())
        {
            while (!exit_game)
            {
                utilities::time::sleep_sec(1);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        exit_game = true;
    }

    bool game::initialise()
    {
        return true;
    }

    void game::shutdown()
    {

    }
}
