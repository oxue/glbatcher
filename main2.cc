#define GLEW_STATIC
#include <GL/glew.h>
#include "BatchContext.h"
#include "Batch.h"
#include "Sprite.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>

const GLchar* vertexSource = 
"#version 150\n"

"in vec2 position;"
"in vec2 texcoord;"
"in float rotation;"

"out vec2 Texcoord;"

"void main()"
"{"
"    Color = color;"
"    Texcoord = texcoord;"
"    gl_Position = proj * view * model * vec4((position), 0.0, 1.0);"
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
    bt.setTexture(tex);
    Sprite s;
    bt.addSprite(s);

    return 0;
}