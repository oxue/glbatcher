#include "Vec2.h"
#include <stdio.h>

Vec2::Vec2(float _x, float _y):
    x(_x), y(_y)
{

}

void Vec2::print()
{
    printf("Vec2{x:%f y:%f}\n", x, y);
}