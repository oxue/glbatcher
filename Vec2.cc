#include "Vec2.h"
#include <stdio.h>
#include <math>

Vec2::Vec2(float _x, float _y):
    x(_x), y(_y)
{

}

void Vec2::print()
{
    printf("Vec2{x:%f y:%f}\n", x, y);
}

Vec2 Vec2::operator+(const Vec2& _vec){
    return Vec2(x + _vec.x, y + _vec.y);
}

float Vec2::operator*(const Vec2& _vec){
    return x * _vec.x + y * _vec.y;
}

Vec2 Vec2::operator*(float _fac){
    return Vec2(x * _fac, y * _fac);
}

float Vec2::distance(){
    return sqrt((*this)*(*this));;
}

Vec2 Vec2::normalize(){
    float dis = distance();
    return Vec2(x/dis, y/dis);
}

Vec2 Vec2::interpolate(float _length){
    return normalize() * _length;
}
