#ifndef _SHADER_H
#define _SHADER_H

#include <SDL2/SDL_opengl.h>
#include <string>

class Shader
{
private:
    GLuint shaderID;
    std::string source;
    GLenum type;

public:
    Shader(GLenum _type, std::string _source);
    GLenum getType();
    GLuint getID();
    void printShaderLog(GLuint _shader);
};

#endif