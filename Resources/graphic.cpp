#include <string>
#include "declare.h"
#include "Init.h"
#include "graphic.h"
#include "logic.h"
#include "game_states.h"
#include "game.h"
#include "destroy.h"

void renderTexture(SDL_Texture *texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
    
void renderfullscreen(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void loadtext( const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect flappybirdrect) {
    TTF_Font* font = TTF_OpenFont(fontstyle, size);
    SDL_Surface* text = TTF_RenderText_Solid(font, s, color);
    SDL_Texture* texttf = SDL_CreateTextureFromSurface(renderer, text);
    SDL_RenderCopy(renderer, texttf, NULL, &flappybirdrect);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texttf);
    TTF_CloseFont(font);
}

void loadtext1(SDL_Renderer* targetRenderer, const char* fontFile, int size, SDL_Color color, const char* text, int x, int y) {
    TTF_Font* font = TTF_OpenFont(fontFile, size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(targetRenderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    } else {
        SDL_Rect dst = {x, y, surface->w, surface->h};
        SDL_RenderCopy(targetRenderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void scrollingbackground(SDL_Texture *texture)
{
    bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
    if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;
    renderfullscreen(texture, bgPosition, 0);
    renderfullscreen(texture, bgPosition + SCREEN_WIDTH, 0);
}

void updateScoreTexture(const string& scoreText, SDL_Texture*& texture, SDL_Rect& rect) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font1, scoreText.c_str(), white);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}
