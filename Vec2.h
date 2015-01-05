#ifndef _VEC2_
#define _VEC2_

class Vec2{
public:
    float x, y;

    Vec2(float _x = 0, float _y = 0);

    Vec2 operator+(const Vec2& _vec);
    void print();
};

#endif