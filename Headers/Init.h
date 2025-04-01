#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "declare.h"

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL();

SDL_Renderer* createRenderer();

void init();

void quitSDL();

#endif 
