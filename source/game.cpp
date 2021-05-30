/// @file game.cpp

#include "game.hpp"
#include "time.hpp"

namespace core
{
    game::game()
    {
        m_event_exit.subscribe(this);
    }

    game::~game()
    {
        m_event_exit.unsubscribe(this);
    }

    void game::run()
    {
        if (initialise())
        {
            while (!m_exit_game)
            {
                utilities::time::sleep_sec(1);
            }

            shutdown();
        }
    }

    void game::exit()
    {
        // Publish exit event so all subscribers can terminate cleanly
        m_event_exit.publish();
    }

    void game::on_publish(const std::string& event_id, const messaging::event_args* p_event_args)
    {
        if (event_id == "EXIT_GAME")
        {
            // Exit the game loop
            m_exit_game = true;
        }
    }

    bool game::initialise()
    {
        return true;
    }

    void game::shutdown()
    {

    }
}
