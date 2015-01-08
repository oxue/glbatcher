#include "ShaderProgram.h"
#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <string>

ShaderProgram::ShaderProgram(Shader _vertexShader, 
                             Shader _fragmentShader, 
                             int _bytesPerVertex):
    vertexShader(_vertexShader), 
    fragmentShader(_fragmentShader),
    bytesPerVertex(_bytesPerVertex)
{
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader.getID());
    glAttachShader(programID, fragmentShader.getID());
    glLinkProgram(programID);

    GLint programLinked = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &programLinked);
    if(programLinked == GL_FALSE)
    {
        printf("Failed to link program: %d!\n", programID);
        printProgramLog(programID);
    }
}

GLuint ShaderProgram::getAttribLocation(const char* _name)
{
    return glGetAttribLocation(programID, _name);
}

void ShaderProgram::setUniformMatrix4(const char* _name, const GLfloat* _mat)
{
    glUniformMatrix4fv(glGetUniformLocation(programID, _name), 1, GL_FALSE, _mat);
}

void ShaderProgram::setUniformInt1(const char* _name, int value)
{
    glUniform1i(glGetUniformLocation(programID, _name), value);
}

int ShaderProgram::getBytesPerVertex(){
    return bytesPerVertex;
}

void ShaderProgram::printProgramLog( GLuint _program ){
    if( glIsProgram( _program ) ){
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetProgramiv( _program, GL_INFO_LOG_LENGTH, &maxLength );
        char* infoLog = new char[ maxLength ];
        glGetProgramInfoLog( _program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 ) {
            printf( "%s\n", infoLog );
        }
        delete[] infoLog;
    }
    else{
        printf( "Name %d is not a program\n", _program );
    }
}

void ShaderProgram::bind(){
    glUseProgram(programID);
}