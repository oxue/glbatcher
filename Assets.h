#define GLEW_STATIC
#include <GL/glew.h.>

#include <SOIL/SOIL.h>
#include <SDL2/SDL.h>
#include <map>
#include "UVCoords.h"

struct TextureFrame{
    GLuint textureID;
    UVCoords texFrame;
};

std::map* assetMap;
bool isInit = false;

bool QSB_AssetsInitialize()
{
    assetMap = std::map<std::string, TextureFrame>();
    isInit = true;
}

bool loadIntoAssets(std::string _path)
{
    TextureFrame f;
    f.UVCoords = UVCoords(0,0,1,1);
    
    int width, height;
    // TODO change to 32 bit textures later
    unsigned char* image = 
        SOIL_load_image(_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    if(!image) return false;

    glGenTextures(1, &(f.textureID));
    glBindTexture(GL_TEXTURE_2D, f.textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    assetMap[_path] = f;

    return true;
}