#ifndef _SHADERPROGRAM_H
#define _SHADERPROGRAM_H

#define GLEW_STATIC
#include <GL/glew.h>
#include "Shader.h"
#include <SDL2/SDL_opengl.h>

class ShaderProgram{

private:
    Shader fragmentShader;
    Shader vertexShader;

    GLuint programID;

public:
    ShaderProgram(Shader _vertexShader, Shader _fragmentShader);
    void bind();
};
#endif