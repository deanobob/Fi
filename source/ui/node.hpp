/// @file node.hpp

#ifndef NODE_HPP
#define NODE_HPP

#include <climits>
#include <list>
#include <memory>
#include "alignment.hpp"
#include "draw_manager.hpp"
#include "key.hpp"
#include "layout_mode.hpp"
#include "measure_mode.hpp"
#include "mouse.hpp"

/// @brief ui namespace
namespace ui
{
    /// @brief The base class for all UI elements
    class node
    {
        public:
        /// @brief Value that indicates the node should fill the available width
        static constexpr int MAX_WIDTH = -1;
        /// @brief Value that indicates the node should fill the available height
        static constexpr int MAX_HEIGHT = -1;

        /// @brief Construct a new node object
        node() = default;

        /// @brief Destroy the node object
        virtual ~node() = default;

        /// @brief Initialises the node
        void initialise();

        /// @brief Calculates the layout of the node and children
        void layout();

        /// @brief Measures the node and its children
        void measure();

        /// @brief Render the node
        /// @param p_draw_manager The draw manager
        void draw(core::draw_manager* p_draw_manager);

        /// @brief Add a child node
        /// @param p_node The child node
        void add_child(std::unique_ptr<node> p_node);

        /// @brief Invalidate the node, flagging it to be remeasured on next update
        void invalidate();

        /// @brief Set the x position
        /// @param x The x position
        void set_x(float x);

        /// @brief Set the y position
        /// @param y The y position
        void set_y(float y);

        /// @brief Get X position of the node within the world
        /// @return The node world X position
        float get_world_x() const;

        /// @brief Get Y position of the node within the world
        /// @return The node world Y position
        float get_world_y() const;

        /// @brief Set the width
        /// @param width The node width
        void set_width(float width);

        /// @brief Set the height
        /// @param height The node height
        void set_height(float height);

        /// @brief Set the min width
        /// @param min_width The min width
        void set_min_width(float min_width);

        /// @brief Set the min height
        /// @param min_height The min height
        void set_min_height(float min_height);

        /// @brief Set the max width
        /// @param max_width The max width
        void set_max_width(float max_width);

        /// @brief Set the max height
        /// @param max_height The max height
        void set_max_height(float max_height);

        /// @brief Set the X axis padding
        /// @details Child element positioning is offset on the X axis
        /// @param padding The number of pixels to pad by
        void set_padding_x(float padding);

        /// @brief Get the X axis padding
        /// @return The padding value of the X axis
        float get_padding_x() const;

        /// @brief Set the Y axis padding
        /// @details Child element positioning is offset on the Y axis
        /// @param padding The number of pixels to pad by
        void set_padding_y(float padding);

        /// @brief Get the Y axis padding
        /// @return The padding value of the Y axis
        float get_padding_y() const;

        /// @brief Set the X axis margin
        /// @details This element positioning is offset on the X axis
        /// @param margin The number of pixels to offset by
        void set_margin_x(float margin);

        /// @brief Set the Y axis margin
        /// @details This element position is offset on the Y axis
        /// @param margin The number of pixels to offset by
        void set_margin_y(float margin);

        /// @brief Gets the width of the node
        /// @return The width of the node
        float get_width() const;

        /// @brief Gets the height of the node
        /// @return The height of the node
        float get_height() const;

        /// @brief Set the horizontal alignment object
        /// @param alignment The horizontal alignment
        void set_horizontal_alignment(horizontal_alignment alignment);

        /// @brief Set the vertical alignment object
        /// @param alignment The vertical alignment
        void set_vertical_alignment(vertical_alignment alignment);

        /// @brief Set whether the node can have focus  
        /// @param focusable True if focusable, else False
        void set_focusable(bool focusable = true);

        /// @brief Called when the node is focused
        void focused();

        /// @brief Called when the node is unfocused
        void unfocused();

        /// @brief Get the focused state of the node
        /// @return True on success, else false
        bool is_focused() const;

        /// @brief Called on the event a key is pressed
        /// @param key_code The key that was pressed
        virtual void key_pressed(const input::key key_code) {};

        /// @brief Called on the event a key is released
        /// @param key_code The key that was released
        virtual void key_released(const input::key key_code) {};

        /// @brief Called on the event a mouse button is pressed
        /// @param mouse_button The mouse button
        /// @param x_position The x coordinate
        /// @param y_position The y coordinate
        virtual void mouse_button_pressed(const input::mouse_button mouse_button, int x_position, int y_position) {};

        /// @brief Called on the event a mouse button is released
        /// @param mouse_button The mouse button
        /// @param x_position The x coordinate
        /// @param y_position The y coordinate
        virtual void mouse_button_released(const input::mouse_button mouse_button,
                                           int x_position,
                                           int y_position) {};

        /// @brief Called on the event the mouse is moved
        /// @param position_x The mouse x coordinate
        /// @param position_y The mouse y coordinate
        /// @param position_z The mouse wheel position
        virtual void mouse_axis_changed(int position_x, int position_y, int position_z) {};

        protected:
        /// @brief The node x position
        float m_x{0};

        /// @brief The node y position
        float m_y{0};

        /// @brief The parent node
        node* mp_parent{nullptr};

        /// @brief Called when the node is initialised
        virtual void on_initialise() = 0;

        /// @brief Called when the node layout is calculated
        virtual void on_layout() = 0;

        /// @brief Called when the node is drawn allowing child nodes to execute draw functions
        /// @param p_manager The draw manager
        virtual void on_draw(core::draw_manager* p_manager) = 0;

        /// @brief Called when the node is focused
        virtual void on_focus() {};

        /// @brief Called when the node is unfocused
        virtual void on_focus_lost() {};

        /// @brief Set the parent object
        /// @param p_node The parent node
        virtual void set_parent(node* p_node);

        /// @brief Get the node at given coordinates
        /// @param x The x coordinate
        /// @param y The y coordinate
        /// @return node* The node at the given coordinates
        node* get_node_at(float x, float y);
        
        /// @brief Get the focusable node at given coordinates
        /// @param x The x coordinate
        /// @param y The y coordinate
        /// @return node* The node at the given coordinates
        node* get_focusable_node_at(float x, float y);

        private:
        /// @brief Flag indicating if the node needs to be realigned / measured
        bool m_invalid{true};

        /// @brief Flag indicating if the node is focusable
        bool m_focusable{true};

        /// @brief Flag indicating if node has focus
        bool m_focused{false};

        /// @brief The minimum width of the node
        float m_min_width{0.0f};

        /// @brief The minimum height of the node
        float m_min_height{0.0f};

        /// @brief The maximum width of the node
        float m_max_width{static_cast<float>(INT_MAX)};

        /// @brief The maximum height of the node
        float m_max_height{static_cast<float>(INT_MAX)};

        /// @brief The width of the node
        float m_width{MAX_WIDTH};

        /// @brief The height of the node
        float m_height{MAX_HEIGHT};

        /// @brief The distance to offset child elements by on the X axis
        float m_padding_x{0};

        /// @brief The distance to offset child elements by on the Y axis
        float m_padding_y{0};

        /// @brief The distance to offset this element by from its parent on the X axis
        float m_margin_x{0};

        /// @brief The distance to offset this element by from its parent on the Y axis
        float m_margin_y{0};

        /// @brief The horizontal alignment
        horizontal_alignment m_h_align{horizontal_alignment::left};

        /// @brief The vertical alignment
        vertical_alignment m_v_align{vertical_alignment::top};

        /// @brief The mode used to position the node horizontally
        layout_mode m_h_layout_mode{layout_mode::align};

        /// @brief The mode used to position the node vertically
        layout_mode m_v_layout_mode{layout_mode::align};

        /// @brief The horizontal measure mode - defines how the required width is measured
        measure_mode m_h_measure_mode{measure_mode::inflate};

        /// @brief The vertical measure mode - defines how the required height is measured
        measure_mode m_v_measure_mode{measure_mode::inflate};

        /// @brief List of child nodes
        std::list<std::unique_ptr<node> > m_children{};

        /// @brief Align the position of the node horizontally
        void align_horizontal();

        /// @brief Align the position of the node vertically
        void align_vertical();

        /// @brief Calculates the node horizontal alignment
        /// @param x1 The first x Position
        /// @param x2 The second x position
        /// @param alignment The alignment
        /// @param padding The padding
        /// @param margin The margin
        /// @return The calculated horizontal alignment
        static float calculate_alignment(float x1, float x2, horizontal_alignment alignment, float padding, float margin);

        /// @brief Calculates the node vertical alignment
        /// @param y1 The first y Position
        /// @param y2 The second y position
        /// @param alignment The alignment
        /// @param padding The padding
        /// @param margin The margin
        /// @return The calculated horizontal alignment
        static float calculate_alignment(float y1, float y2, vertical_alignment alignment, float padding, float margin);
    };
} /// namespace ui

#endif /// NODE_HPP
