#ifndef _BATCHCONTECT_H_
#define _BATCHCONTECT_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include "Batch.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <string>

class BatchContext
{
public:
    BatchContext();

    bool initialize(std::string _windowLabel = "default", int _w = 800, 
        int _h = 600);
    void addBatch(Batch _batch);
    void drawBatches();
    void clear();

private:
    SDL_Window* window;
    SDL_GLContext context;
};

#endif