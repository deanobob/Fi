/// @file rectangle.hpp

#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "point.hpp"
#include "vector2.hpp"

namespace utilities
{
    class rectangle
    {
        public:
        static const rectangle EMPTY;

        float x{0};
        float y{0};
        float width{0};
        float height{0};

        rectangle();
        rectangle(float x, float y, float width, float height);

        vector2 get_position() const;
        float get_left() const;
        float get_right() const;
        float get_top() const;
        float get_bottom() const;
        vector2 get_centre() const;
        float get_centre_x() const;
        float get_centre_y() const;
        bool contains(float x, float y) const;
        bool contains(const point& value) const;
        bool contains(const vector2& value) const;
        bool contains(const rectangle& value) const;
        bool intersects(const rectangle& value) const;

        bool operator== (const rectangle& rhs) const;
        bool operator!= (const rectangle& rhs) const;
    };
} /// namespace utilities

#endif /// RECTANGLE_HPP
