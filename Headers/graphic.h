#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "declare.h"

using namespace std;

void renderTexture(SDL_Texture *texture, SDL_Rect rect);

SDL_Texture* loadTexture(const char* filename);

void loadtext( const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect flappybirdrect);

void loadtext_Realsize(SDL_Renderer* targetRenderer, const char* fontFile, int size, SDL_Color color, const char* text, int x, int y);

void renderfullscreen(SDL_Texture* texture, int x, int y);

void scrollingbackground(SDL_Texture* texture);

void updateScoreTexture(const string& scoreText, SDL_Texture*& texture, SDL_Rect& rect);

#endif 
