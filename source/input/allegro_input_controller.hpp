/// @file allegro_input_controller.hpp

#ifndef ALLEGRO_INPUT_HPP
#define ALLEGRO_INPUT_HPP

#ifndef CI

#include <list>
#include <map>
#include "allegro5/allegro.h"
#include "input_controller.hpp"

namespace input
{
    /// @brief Implementation of input input interface using liballegro
    class allegro_input_controller
        : public input_controller
    {
        public:
        /// @brief Constructor
        /// @param p_event_queue The allegro event queue
        allegro_input_controller(ALLEGRO_EVENT_QUEUE* p_event_queue = nullptr);

        bool initialise() override;

        void process_events() override;

        void shutdown() override;

        private:
        /// @brief The allegro event queue
        ALLEGRO_EVENT_QUEUE* mp_event_queue{nullptr};

        /// @brief Convert allegro key code to key code
        /// @param key_code The allegro key code
        /// @return The game key code
        static input::key allegro_key_to_key(unsigned int key_code);

        /// @brief Convert allegro mouse button to mouse button
        /// @param button_id The allegro mouse button
        /// @return The game mouse button
        static input::mouse_button allegro_mouse_button_to_mouse_button(unsigned int button_id);
    };

} /// namespace input

#else /// CI

#include "input_controller.hpp"

namespace input
{
    /// @brief Implementation of input controller interface using liballegro
    class allegro_input_controller: public input_controller
    {
        public:
        /// @brief Constructor
        allegro_input_controller() = default;

        bool initialise() override;

        void process_events() override;

        void shutdown() override;
    };

} /// namespace input

#endif /// CI

#endif /// ALLEGRO_INPUT_HPP
