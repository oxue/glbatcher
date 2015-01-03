#include "Sprite.h"
#include "UVCoords.h"

Sprite::Sprite(float _x, float _y, UVCoords _uvc):
    position(_x, _y), texFrame(_uvc){
    
}