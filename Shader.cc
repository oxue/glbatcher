#include "Shader.h"
#include <string>
#include <SDL2/SDL_opengl.h>
#include <stdio.h>

Shader::Shader(GLenum _type, std::string _source):
    type(_type), source(_source)
{
    shaderID = glCreateShader(_type);
    const char* msource = _source.c_str();
    glShaderSource(shaderID, 1, &msource, NULL);
    glCompileShader(shaderID);

    GLint isCompiled = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){
        printf("Unable to compile shader: %d", shaderID);
        printShaderLog(shaderID);
    }
}

void Shader::printShaderLog( GLuint _shader ){
    if( glIsShader( _shader ) ){
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetShaderiv( _shader, GL_INFO_LOG_LENGTH, &maxLength );
        char* infoLog = new char[ maxLength ];
        glGetShaderInfoLog( _shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 ){
            printf( "%s\n", infoLog );
        }
        delete[] infoLog;
    }
    else{
        printf( "Name %d is not a shader\n", _shader );
    }
}

GLenum getType()
{
    return _type;
}