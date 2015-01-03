#include "ShaderProgram.h"
#include <SDL2/SDL_opengl.h>

ShaderProgram::ShaderProgram(Shader _vertexShader, Shader _fragmentShader):
    vertexShader(_vertexShader), fragmentShader(_fragmentShader)
{
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint programLinked = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &programLinked);
    if(programLinke == GL_FALSE)
    {
        printf("Failed to link program: %d!\n", programID);
        printProgramLog(programID);
    }
}

void ShaderProgram::bind()
{

}