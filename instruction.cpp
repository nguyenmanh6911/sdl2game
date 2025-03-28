#include "declare.h"
#include "Init.h"
#include "instruction.h"
#include "graphic.h"

void showInstructionWindow() {
    SDL_Window* instructionWindow = SDL_CreateWindow("How to Play",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(instructionWindow, -1, SDL_RENDERER_ACCELERATED);
   SDL_Texture* bgTexture = IMG_LoadTexture(renderer,"instruction_bg.png");
    instructionWindowRunning = true;

    SDL_Event event;
    while (instructionWindowRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                instructionWindowRunning = false;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
                if (event.window.windowID == SDL_GetWindowID(instructionWindow)) {
                    instructionWindowRunning = false;
                }
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL); 
        SDL_RenderPresent(renderer);

        SDL_Delay(16); 
    }
    SDL_DestroyTexture(bgTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(instructionWindow);
    instructionWindowRunning = false;
}