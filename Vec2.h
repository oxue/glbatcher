#ifndef _VEC2_
#define _VEC2_

class Vec2{
public:
    float x, y;

    Vec2(float _x = 0, float _y = 0);

    Vec2 operator+(const Vec2& _vec);
    Vec2 operator*(float _fac);
    float operator*(const Vec2& _vec);
    float distance();
    Vec2 normalize();
    Vec2 interpolate(float _length);
    void print();
};

#endif