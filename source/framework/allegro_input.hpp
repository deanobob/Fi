/// @file allegro_input.hpp

#ifndef ALLEGRO_INPUT_HPP
#define ALLEGRO_INPUT_HPP

#ifndef CI

#include <list>
#include <map>
#include "allegro5/allegro.h"
#include "input.hpp"

namespace framework
{
    /// @brief Implementation of input framework interface using liballegro
    class allegro_input: public input
    {
        public:
        /// @brief Constructor
        /// @param p_event_queue The allegro event queue
        allegro_input(ALLEGRO_EVENT_QUEUE* p_event_queue = nullptr);

        bool initialise() override;

        void process_events() override;

        void shutdown() override;

        private:
        /// @brief The allegro event queue
        ALLEGRO_EVENT_QUEUE* mp_event_queue{nullptr};
    };

} /// namespace framework

#else /// CI

#include "input.hpp"

namespace framework
{
    /// @brief Implementation of input framework interface using liballegro
    class allegro_input: public input
    {
        public:
        /// @brief Constructor
        allegro_input() = default;

        bool initialise() override;

        void process_events() override;

        void shutdown() override;
    };

} /// namespace framework

#endif /// CI

#endif /// ALLEGRO_INPUT_HPP
