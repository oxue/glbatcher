#ifndef _UVCOORDS_H_
#define _UVCOORDS_H_

#include "Vec2.h"

class UVCoords{
public:
    Vec2 topRight;
    Vec2 bottomRight;
    Vec2 bottomLeft;
    Vec2 topLeft;

    UVCoords(float _x = 0, float _y = 0, float _w = 0, float _h = 0);
    void print();
};

#endif