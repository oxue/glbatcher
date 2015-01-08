#ifndef _BATCHCONTEXT_H_
#define _BATCHCONTEXT_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include "Batch.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Batch;

class BatchContext
{
public:
    BatchContext();

    bool initialize(std::string _windowLabel = "default", int _w = 800, 
        int _h = 600);
    void addBatch(Batch _batch);
    void drawBatches();
    void clear();

    int screenW;
    int screenH;

public:
    SDL_Window* window;
    SDL_GLContext context;

    glm::mat4 get2DMatrix() const;
};

#endif