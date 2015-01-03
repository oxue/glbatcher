#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SOIL/SOIL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Vec2.h"
#include "UVCoords.h"

const GLchar* vertexSource = 
"#version 150\n"

"in vec2 position;"
"in vec3 color;"
"in vec2 texcoord;"

"out vec3 Color;"
"out vec2 Texcoord;"

"uniform mat4 model;"
"uniform mat4 view;"
"uniform mat4 proj;"

"void main()"
"{"
"    Color = color;"
"    Texcoord = texcoord;"
"    gl_Position = proj * view * model * vec4((position), 0.0, 1.0);"
"}";

const GLchar* fragmentSource = 
"#version 150\n"

"in vec3 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"

"uniform sampler2D tex;"
"uniform sampler2D tex2;"
"uniform float mixVal;"

"void main()"
"{"
"    vec4 t1 = texture(tex, Texcoord + vec2(sin(Texcoord.y * 5)),0) * vec4(1,1,1, 1.0);"
"    vec4 t2 = texture(tex2, Texcoord + vec2(sin(Texcoord.y  * 5)),0) * vec4(1,1,1, 1.0);"
"    outColor = mix(t1, t2, mixVal);"
"}";

int main(int argc, char *argv[])
{
    Vec2 v(10.0f,10.0f);
    v.print();

    UVCoords uv(0,0,100,100);
    uv.print();

    // SDL GL initialization
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // GLEW initialization
    glewExperimental = GL_TRUE;
    glewInit();

    // Vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex data
    float vertices[] = {
    //  Position      Color             Texcoords
        -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Vertex buffer
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    printf("%u\n", vertexBuffer);

    // Upload data to buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element Buffer
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                 GL_STATIC_DRAW);

    // Texture object
    GLuint tex[2];
    glGenTextures(2, tex);

    // You can also use mip maps
    int width,height;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    unsigned char* image = 
        SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, 
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    image = 
        SOIL_load_image("img2.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    // Texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Create shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Create and link program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Select program
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // Last 2 parameters specifies the layout in unit bytes
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
     0);
    glEnableVertexAttribArray(posAttrib);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(colAttrib);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                          (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(texAttrib);

    glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 0);

    GLint mixValLoc = glGetUniformLocation(shaderProgram, "mixVal");

    glm::mat4 trans;
    trans = glm::rotate(trans, 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniTrans,1,GL_FALSE, glm::value_ptr(trans));

    glm::mat4 view = glm::lookAt(
        glm::vec3(1.2f,1.2f,1.2f),
        glm::vec3(0.0f,0.0f,0.0f),
        glm::vec3(0.0f,0.0f,1.0f)
    );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));


    SDL_Event windowEvent;

    float mv = 1.0;

    while (true)
    {
        mv-=0.01;
        if(mv<=0)
            mv = 1;

        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
            if (windowEvent.type == SDL_KEYUP &&
                windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
        }
        glm::mat4 trans;
        trans = glm::rotate(trans, mv*180, glm::vec3(0.0f, 0.0f, 1.0f));

        GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(uniTrans,1,GL_FALSE, glm::value_ptr(trans));
        glUniform1f(mixValLoc, mv);

        glClear(GL_COLOR_BUFFER_BIT); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}