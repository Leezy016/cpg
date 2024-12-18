#include<cmath>
#include "Vec2.h"

bool Vec2::operator==(const Vec2 &rhs) const
{
    return (x==rhs.x && y==rhs.y);
}

bool Vec2::operator!=(const Vec2 &rhs) const
{
    return (x!=rhs.x || y!=rhs.y);
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float val) const
{
    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator/(const float val) const
{
    return Vec2(x / val, y / val);
}

float Vec2::dist(const Vec2& rhs) const
{
    return sqrt((x-rhs.x)*(x - rhs.x)+ (y - rhs.y) * (y - rhs.y));
}

