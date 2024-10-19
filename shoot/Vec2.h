#pragma once

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float xin, float yin)
        :x(xin),y(yin){}

    bool operator == (const Vec2 & rhs) const;
    bool operator != (const Vec2 & rhs) const;

    bool operator + (const Vec2 & rhs) const;
    bool operator - (const Vec2 & rhs) const;
    bool operator * (const float val) const;
    bool operator / (const float val) const;

    bool operator += (const Vec2 & rhs) const;
    bool operator -= (const Vec2 & rhs) const;
    bool operator *= (const float val) const;
    bool operator /= (const float val) const;

    float dist(const Vec2 & rhs) const;
};
