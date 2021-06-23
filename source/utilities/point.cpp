/// @file point.cpp

#include "point.hpp"

namespace utilities
{
    const point point::ZERO(0, 0);
    const point point::ONE(1, 1);

    point::point()
        : point(0, 0)
    {

    }

    point::point(const point& point)
    {
        this->x = point.x;
        this->y = point.y;
    }

    point::point(const int x, const int y)
    {
        this->x = x;
        this->y = y;
    }

    point point::operator+ (const point& rhs) const
    {
        return point(this->x + rhs.x, this->y + rhs.y);
    }

    point& point::operator+= (const point& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }

    point point::operator- (const point& rhs) const
    {
        return point(this->x - rhs.x, this->y - rhs.y);
    }

    point& point::operator-= (const point& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;

        return *this;
    }

    point point::operator* (const point& rhs) const
    {
        return point(this->x * rhs.x, this->y * rhs.y);
    }

    point& point::operator*= (const point& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;

        return *this;
    }

    point point::operator/ (const point& rhs) const
    {
        return point(this->x / rhs.x, this->y / rhs.y);
    }

    point& point::operator/= (const point& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;

        return *this;
    }

    bool point::operator== (const point& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }

    bool point::operator!= (const point& rhs) const
    {
        return !(*this == rhs);
    }
}
