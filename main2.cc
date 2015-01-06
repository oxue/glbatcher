#define GLEW_STATIC
#include <GL/glew.h>
#include "BatchContext.h"
#include "Batch.h"
#include "Sprite.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include "UVCoords.h"

const GLchar* vertexSource = 
"#version 150\n"

"in vec2 position;"
"in vec2 texcoord;"
"in float rotation;"

"out vec2 Texcoord;"

"void main()"
"{"
"    Texcoord = texcoord;"
"    vec2 rotPos = vec2(0,0);"
"    rotPos.x = position.x * cos(rotation) - position.y * sin(rotation);"
"    rotPos.y = position.x * sin(rotation) + position.y * cos(rotation);"
"    gl_Position = vec4(rotPos, 0.0, 1.0);"
"}";

const GLchar* fragmentSource = 
"#version 150\n"

"in vec2 Texcoord;"

"out vec4 outColor;"

"uniform sampler2D tex;"

"void main()"
"{"
"    outColor = texture(tex, Texcoord);"
"}";

int main()
{


    BatchContext b;
    b.initialize();

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err!=GLEW_OK)
    {
      printf("not ok\n");
    }


    ShaderProgram program(Shader(GL_VERTEX_SHADER, vertexSource),
                          Shader(GL_FRAGMENT_SHADER, fragmentSource),
                          20);

    // Texture object
    GLuint tex;
    glGenTextures(1, &tex);

    // You can also use mip maps
    int width,height;

    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, tex);
    unsigned char* image = 
        SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, 
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    Batch bt(&program);
    bt.setAttribute("position",2,GL_FLOAT,5 * sizeof(float), 0);
    bt.setAttribute("texcoord",2,GL_FLOAT,5 * sizeof(float), 2 * sizeof(float));
    bt.setAttribute("rotation",1,GL_FLOAT,5 * sizeof(float), 4 * sizeof(float));
    bt.setTexture(tex);
    Sprite s(0,0,1,1,UVCoords(0,0,1,1));
    s.rotation = 3.14/2;
    bt.addSprite(s);
    bt.render();

    SDL_GL_SwapWindow((b.window));

    getchar();

    return 0;
}