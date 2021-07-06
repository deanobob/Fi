/// @file keyboard_state.hpp

#ifndef KEYBOARD_STATE_HPP
#define KEYBOARD_STATE_HPP

#include <list>
#include "key.hpp"

/// @namespace services namespace
namespace services
{
    /// @brief Class that stores the current keyboard state
	class keyboard_state
	{
		public:
			/// @brief Set the key pressed state
			/// @param key The key
			/// @param pressed True if pressed, false if not pressed
			void set_key_state(key key, bool pressed);

			/// @brief Check if the key is pressed
			/// @param key The key
			/// @return True if pressed, false if not pressed
			bool is_key_pressed(key key) const;

		private:
			/// @brief List containing all the currently pressed keys
			std::list<key> m_pressed_key_list{};
	};
} /// namespace services

#endif /// KEYBOARD_STATE_HPP
