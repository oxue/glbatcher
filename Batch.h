#ifndef _BATCH_H_
#define _BATCH_H_

#include "Sprite.h"
#include <SDL2/SDL_opengl.h>
#include "ShaderProgram.h"
#include "BatchContext.h"
#include <glm/glm.hpp>

#define MAX_SPRITE_COUNT 10
#define INDEXES_PER_SPRITE 6
#define writeData(_type, _des, _src)\
    *((_type*)(_des)) = (_src);\
     (_des) = (char*)(_des) + sizeof(_type)

class BatchContext;

class Batch
{
private:
    Sprite* sprites;
    GLuint vertexBuffer;
    GLuint indexBuffer;
    GLuint vertexArrayObject;
    GLuint* indexArray;
    char* vertexArray;
    GLuint textureID;

    int vertexCount;
    int indexCount;
    int spriteCount;

    glm::mat4 viewPortMatrix;
    int zoom;

    ShaderProgram* pShaderProgram;

public:
    Batch(const BatchContext& _batchContext);
    Batch(const BatchContext& _batchContext, ShaderProgram* _program);

    void addSprite(Sprite _sprite);
    void render();
    void setTexture(GLuint _textureID);
    void setShaderProgram(ShaderProgram* _program);
    void setAttribute(const char* _name, 
                      GLint _ncomps, 
                      GLenum _type, 
                      GLsizei _stride, 
                      GLuint _start);

private:
    void uploadSprite(Sprite &_sprite);
};

#endif