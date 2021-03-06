/// @file vector2.cpp

#include <float.h>
#include <math.h>
#include "math.hpp"
#include "vector2.hpp"

namespace utilities
{
    const vector2 vector2::ZERO(0.0f, 0.0f);
    const vector2 vector2::ONE(1.0f, 1.0f);
    const vector2 vector2::MAX(FLT_MAX, FLT_MAX);

    double vector2::distance(const vector2& v1, const vector2& v2)
    {
        double xDist = v2.x - v1.x;
        double yDist = v2.y - v1.y;

        return sqrt((xDist * xDist) + (yDist * yDist));
    }

    float vector2::dot(const vector2& v1, const vector2& v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }

    vector2 vector2::normalise(const vector2& value)
    {
        float v = 1.0f / (float)sqrt((value.x * value.x) + (value.y * value.y));

        return vector2(value.x * v, value.y * v);
    }

    vector2 vector2::clamp(const vector2& value, const vector2& min, const vector2& max)
    {
        return vector2(utilities::math::clamp(value.x, min.x, max.x),
                       utilities::math::clamp(value.y, min.y, max.y));
    }

    vector2 vector2::perp(const vector2& vector)
    {
        // Anti-clockwise winding - negate the Y value
        return vector2(vector.y, -vector.x);
    }

    vector2 vector2::lerp(const vector2& a, const vector2& b, float t)
    {
        float ret_x = utilities::math::lerp(a.x, b.x, t);
        float ret_y = utilities::math::lerp(a.y, b.y, t);
        return {ret_x, ret_y};
    }

    vector2 vector2::min(const vector2& lhs, const vector2& rhs)
    {
        return vector2(fmin(lhs.x, rhs.x), fmin(lhs.y, rhs.y));
    }

    vector2 vector2::max(const vector2& lhs, const vector2& rhs)
    {
        return vector2(fmax(lhs.x, rhs.x), fmax(lhs.y, rhs.y));
    }
    
    vector2 vector2::forward(float angle_rad)
    {
        return vector2(cos(angle_rad), sin(angle_rad));
    }

    utilities::vector2 vector2::rotate_point(float cx, float cy, float angle_rad, float px, float py)
    {
        float s = sin(angle_rad);
        float c = cos(angle_rad);

        // translate point back to origin:
        px -= cx;
        py -= cy;

        // rotate point
        float xnew = px * c - py * s;
        float ynew = px * s + py * c;

        // translate point back:
        px = xnew + cx;
        py = ynew + cy;

        return {px, py};
    }

    vector2::vector2()
        : vector2(0.0f, 0.0f)
    {

    }

    vector2::vector2(const vector2& value)
    {
        this->x = value.x;
        this->y = value.y;
    }

    vector2::vector2(const int x, const int y)
    {
        this->x = static_cast<float>(x);
        this->y = static_cast<float>(y);
    }

    vector2::vector2(const float x, const float y)
    {
        this->x = x;
        this->y = y;
    }

    vector2& vector2::operator=(const utilities::vector2& other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }

    vector2 vector2::operator-() const
    {
        vector2 v{};
        v.x = -this->x;
        v.y = -this->y;
        return v;
    }

    vector2 vector2::operator+ (const vector2& rhs) const
    {
        return vector2(this->x + rhs.x, this->y + rhs.y);
    }

    vector2& vector2::operator+= (const vector2& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;

        return *this;
    }

    vector2 vector2::operator+ (const double& rhs) const
    {
        return vector2(this->x + static_cast<float>(rhs), this->y + static_cast<float>(rhs));
    }

    vector2& vector2::operator+= (const double& rhs)
    {
        this->x += static_cast<float>(rhs);
        this->y += static_cast<float>(rhs);

        return *this;
    }

    vector2 vector2::operator- (const vector2& rhs) const
    {
        return vector2(this->x - rhs.x, this->y - rhs.y);
    }

    vector2& vector2::operator-= (const vector2& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;

        return *this;
    }

    vector2 vector2::operator* (const vector2& rhs) const
    {
        return vector2(this->x * rhs.x, this->y * rhs.y);
    }

    vector2 vector2::operator* (const double& rhs) const
    {
        return vector2(this->x * static_cast<float>(rhs), this->y * static_cast<float>(rhs));
    }

    vector2& vector2::operator*= (const vector2& rhs)
    {
        this->x *= rhs.x;
        this->y *= rhs.y;

        return *this;
    }

    vector2 vector2::operator/ (const vector2& rhs) const
    {
        return vector2(this->x / rhs.x, this->y / rhs.y);
    }

    vector2 vector2::operator/ (const double& rhs) const
    {
        return vector2(this->x / static_cast<float>(rhs), this->y / static_cast<float>(rhs));
    }

    vector2& vector2::operator/= (const vector2& rhs)
    {
        this->x /= rhs.x;
        this->y /= rhs.y;

      return *this;
    }

    bool vector2::operator== (const vector2& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }

    bool vector2::operator!= (const vector2& rhs) const
    {
        return !(*this == rhs);
    }
}
