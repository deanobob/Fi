/// @file rectangle.cpp

#include "rectangle.hpp"

namespace utilities
{
    const rectangle rectangle::EMPTY{};

    rectangle::rectangle()
        : rectangle(0, 0, 0, 0)
    {

    }

    rectangle::rectangle(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    vector2 rectangle::get_position() const
    {
        return vector2(this->x, this->y);
    }

    float rectangle::get_left() const
    {
        return this->x;
    }

    float rectangle::get_right() const
    {
        return this->x + this->width;
    }

    float rectangle::get_top() const
    {
        return this->y;
    }

    float rectangle::get_bottom() const
    {
        return this->y + this->height;
    }

    vector2 rectangle::get_centre() const
    {
        return vector2(this->get_centre_x(), this->get_centre_y());
    }

    float rectangle::get_centre_x() const
    {
        return this->x + (this->width / 2);
    }

    float rectangle::get_centre_y() const
    {
        return this->y + (this->height / 2);
    }

    bool rectangle::contains(float x, float y) const
    {
        return (x >= this->x && x <= (this->x + this->width) && y >= this->y
            && y <= (this->y + this->height));
    }

    bool rectangle::contains(const point& value) const
    {
        return (static_cast<float>(value.x) >= this->x && static_cast<float>(value.x) <= (this->x + this->width)
            && static_cast<float>(value.y) >= this->y && static_cast<float>(value.y) <= (this->y + this->height));
    }

    bool rectangle::contains(const vector2& value) const
    {
        return (value.x >= this->x && value.x <= (this->x + this->width)
            && value.y >= this->y && value.y <= (this->y + this->height));
    }

    bool rectangle::contains(const rectangle& value) const
    {
        return (value.x >= this->x
            && (value.x + value.width) <= (this->x + this->width)
            && value.y >= this->y
            && (value.y + value.height) <= (this->y + this->height));
    }

    bool rectangle::intersects(const rectangle& value) const
    {
        return !(value.x > this->x + this->width || value.x + value.width < this->x
            || value.y > this->y + this->height || value.y + value.height < this->y);
    }

    bool rectangle::operator==(const rectangle& rhs) const
    {
        return (this->x == rhs.x && this->y == rhs.y && this->width == rhs.width
            && this->height == rhs.height);
    }

    bool rectangle::operator!=(const rectangle& rhs) const
    {
        return !(*this == rhs);
    }
}
