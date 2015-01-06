#include "Sprite.h"
#include "UVCoords.h"

Sprite::Sprite(float _x, float _y, float _w, float _h, UVCoords _uvc):
    position(_x, _y), 
    dimensions(_w, _h),
    texFrame(_uvc), 
    rotation(0.5),
    addr(NULL)
{
    
}