#define GLEW_STATIC
#include <GL/glew.h>
#include "BatchContext.h"
#include "Batch.h"
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <string>
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BatchContext::BatchContext() { }

bool BatchContext::initialize(std::string _windowLabel, int _w, int _h){
    screenW = _w;
    screenH = _h;

    // Init SDL OPENGL video
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Create a window and context
    window = SDL_CreateWindow(_windowLabel.c_str(), 
                              100, 
                              100, 
                              _w, 
                              _h, 
                              SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    // glew initialization
    
    return true;
}

glm::mat4 BatchContext::get2DMatrix() const
{
    glm::mat4 sca = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f/800 * 4, -1.0f/600 * 4, 1));
    glm::mat4 trans = glm::translate(sca, glm::vec3(-800/4, -600/4, 0));
    return trans;
}

void BatchContext::addBatch(Batch _batch)
{

}

void BatchContext::drawBatches()
{

}

void BatchContext::clear()
{

}