/// @file point.hpp

#ifndef POINT_HPP
#define POINT_HPP

namespace utilities
{
    class point
    {
        public:
        static const point ZERO;
        static const point ONE;

        int x {0};
        int y {0};

        point();
        point(const point& value);
        point(const int x, const int y);

        point operator+ (const point& rhs) const;
        point& operator+= (const point& rhs);
        point operator- (const point& rhs) const;
        point& operator-= (const point& rhs);
        point operator* (const point& rhs) const;
        point& operator*= (const point& rhs);
        point operator/ (const point& rhs) const;
        point& operator/= (const point& rhs);
        bool operator== (const point& rhs) const;
        bool operator!= (const point& rhs) const;
    };
} /// namespace point

#endif /// POINT_HPP
