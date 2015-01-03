#include "UVCoords.h"
#include <stdio.h>

UVCoords::UVCoords(float _x, float _y, float _w, float _h)
{
    topRight.x = _x + _w;
    topRight.y = _y;

    bottomRight.x = _x + _w;
    bottomRight.y = _y + _h;

    bottomLeft.x = _x;
    bottomLeft.y = _y + _h;

    topLeft.x = _x;
    topLeft.y = _y;
}

void UVCoords::print()
{
    printf("UVCoords{\n");
    printf("  ");
    topRight.print();
    printf("  ");
    bottomRight.print();
    printf("  ");
    bottomLeft.print();
    printf("  ");
    topLeft.print();
    printf("}\n");
}