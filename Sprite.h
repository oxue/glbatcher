#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Vec2.h"
#include "UVCoords.h"
#include <SDL2/SDL.h>

class Sprite{
public:
    Vec2 position;
    float rotation;
    UVCoords texFrame;
    void* addr;

    Sprite(float _x = 0, float _y = 0, UVCoords _uvc = UVCoords());

};

#endif