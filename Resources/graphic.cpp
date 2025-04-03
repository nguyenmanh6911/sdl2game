#include <string>
#include "declare.h"
#include "Init.h"
#include "graphic.h"
#include "logic.h"
#include "game_states.h"
#include "game.h"
#include "destroy.h"

// Hàm render ảnh
void renderTexture(SDL_Texture *texture, SDL_Rect rect) 
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
    
//Hàm render ảnh fullscreen
void renderfullscreen(SDL_Texture* texture, int x, int y) {  
    SDL_Rect dest = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

//Tải ảnh từ file
SDL_Texture* loadTexture(const char* filename) { 
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

//Render text lên vị trí có sẵn
void loadtext( const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect flappybirdrect) {
    TTF_Font* font = TTF_OpenFont(fontstyle, size);
    if (!font) return;
    SDL_Surface* text = TTF_RenderText_Solid(font, s, color);
    if (!text) {
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* texttf = SDL_CreateTextureFromSurface(renderer, text);
    if (!texttf) {
        SDL_FreeSurface(text);  
        TTF_CloseFont(font);
        return;
    } 
    SDL_RenderCopy(renderer, texttf, NULL, &flappybirdrect);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(texttf);
    TTF_CloseFont(font);
}

//Render text giữ nguyên kích thước
void loadtext_Realsize(SDL_Renderer* renderer, const char* fontFile, int size, SDL_Color color, const char* text, int x, int y) {
    TTF_Font* font = TTF_OpenFont(fontFile, size);
    if (!font) {
        return;
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
       return;
    } else {
        SDL_Rect dst = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

// Hàm tạo hiệu ứng chuyển động cho background
void scrollingbackground(SDL_Texture *texture)
{
    bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
    if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;
    renderfullscreen(texture, bgPosition, 0);
    renderfullscreen(texture, bgPosition + SCREEN_WIDTH, 0);
}

// Hàm render điểm số
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
