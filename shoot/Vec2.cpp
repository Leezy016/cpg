#include "Vec2.h"

bool Vec2::operator==(const Vec2 &rhs) const
{
    return (x==rhs.x && y==rhs.y);
}

bool Vec2::operator!=(const Vec2 &rhs) const
{
    return (x!=rhs.x || y!=rhs.y);
}