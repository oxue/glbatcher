#define GLEW_STATIC
#include <GL/glew.h>
#include "Batch.h"
#include <SDL2/SDL_opengl.h>
#include "Vec2.h"
#include <stdio.h>
#include <stdlib.h>

Batch::Batch():
    vertexArray(NULL),
    spriteCount(0),
    vertexCount(0),
    indexCount(0)
{
    // alloc
    sprites = new Sprite[MAX_SPRITE_COUNT];
    indexArray = new GLuint[MAX_SPRITE_COUNT * INDEXES_PER_SPRITE];
}

Batch::Batch(ShaderProgram* _program):
    pShaderProgram(_program), 
    spriteCount(0),
    vertexCount(0),
    indexCount(0)
{
    sprites = new Sprite[MAX_SPRITE_COUNT];
    indexArray = new GLuint[MAX_SPRITE_COUNT * INDEXES_PER_SPRITE];
    vertexArray = 
        new char[MAX_SPRITE_COUNT * (pShaderProgram->getBytesPerVertex())];

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);
}

void Batch::addSprite(Sprite _sprite){
    sprites[spriteCount++] = _sprite;
    uploadSprite(_sprite);
}

void Batch::setShaderProgram(ShaderProgram* _program){
     pShaderProgram = _program;
}

void Batch::setTexture(GLuint _textureID){
    textureID = _textureID;
}

void Batch::setAttribute(const char* _name, 
                         GLint _ncomps, 
                         GLenum _type, 
                         GLsizei _stride, 
                         GLuint _start)
{
    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    GLuint attribLoc = pShaderProgram->getAttribLocation(_name);
    glVertexAttribPointer(attribLoc,
                          _ncomps, 
                          _type,
                          GL_FALSE,
                          _stride,
                          (char*)NULL + _start);
    glEnableVertexAttribArray(attribLoc);
}                         

void Batch::render()
{
    pShaderProgram->bind();
    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexCount * pShaderProgram->getBytesPerVertex(),
                 vertexArray,
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 indexCount * sizeof(GLuint),
                 indexArray,
                 GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    pShaderProgram->setUniformInt1("tex", 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

// Perhaps use templates later on to sepcify own vertex formats
void Batch::uploadSprite(Sprite &_sprite){
    if(pShaderProgram == NULL) {
        printf("No shaderprogram set in Batch, upload Aborted");
        return;
    }
    if(_sprite.addr == NULL){
        // change this
        _sprite.addr = 
            (void*)(vertexArray +
                    vertexCount * (pShaderProgram->getBytesPerVertex()));
    }
    // x y u v r
    void* tmp = _sprite.addr;

    writeData(Vec2, tmp, _sprite.position);
    writeData(Vec2, tmp, _sprite.texFrame.topLeft);
    writeData(float, tmp, _sprite.rotation);

    writeData(Vec2, tmp, _sprite.position + Vec2(_sprite.dimensions.x, 0));
    writeData(Vec2, tmp, _sprite.texFrame.topRight);
    writeData(float, tmp, _sprite.rotation);

    writeData(Vec2, tmp, _sprite.position + _sprite.dimensions);
    writeData(Vec2, tmp, _sprite.texFrame.bottomRight);
    writeData(float, tmp, _sprite.rotation);

    writeData(Vec2, tmp, _sprite.position + Vec2(0, _sprite.dimensions.y));
    writeData(Vec2, tmp, _sprite.texFrame.bottomLeft);
    writeData(float, tmp, _sprite.rotation);

    printf("%f", _sprite.rotation);

    vertexCount += 4;

    GLuint tmpi = indexCount;
    indexArray[indexCount++] = indexCount - 1;
    indexArray[indexCount++] = indexCount - 1;
    indexArray[indexCount++] = indexCount - 2;
    indexArray[indexCount++] = indexCount - 2;
    indexArray[indexCount++] = indexCount - 2;
    indexArray[indexCount++] = indexCount - 6;

    printf("uploaded\n");
}