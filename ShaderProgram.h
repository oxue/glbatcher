#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include <SDL2/SDL_opengl.h>
#include <string>
class ShaderProgram{

private:
    Shader fragmentShader;
    Shader vertexShader;

    GLuint programID;
    int bytesPerVertex;

public:
    ShaderProgram(Shader _vertexShader, Shader _fragmentShader, int _bytesPerVertex);
    void bind();
    void printProgramLog( GLuint _program );
    int getBytesPerVertex();

    void setUniformInt1(const char* _name, int value);
    GLuint getAttribLocation(const char* _name);
};
#endif