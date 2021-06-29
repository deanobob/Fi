/// @file draw_manager.hpp
/// @brief The draw_manager base class

#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "service.hpp"
#include "renderer.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Base class for services
    class draw_manager : public core::service
    {
        public:
        /// @brief Constructor
        /// @param p_game The game instance
        draw_manager(core::game* p_game);
        /// @brief Default destructor
        virtual ~draw_manager() = default;

        /// @brief Initialises the draw_manager reader
        /// @return True if initialised successfully
        bool initialise();
        /// @brief Called on every tick allowing draw_manager input to be processed
        /// @param gametime The gametime maintaining instance
        void update(utilities::gametime& gametime) override;
        /// @brief Shutsdown the service
        void shutdown() override;
        /// @brief Returns false for pausable check, ensuring service runs when game is paused
        /// @return True if pauseable, else false
        bool pauseable() const override;

        private:
        /// @brief Reference to renderer system
        framework::renderer* mp_renderer {nullptr};
    };
} /// namespace services

#endif /// DRAW_MANAGER_HPP
