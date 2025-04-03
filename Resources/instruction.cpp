#include "declare.h"
#include "Init.h"
#include "instruction.h"
#include "graphic.h"

//Hàm hiện cửa sổ hướng dẫn
void showInstructionWindow() {
    //Khởi tạo cửa sổ và renderer mới
    SDL_Window* instructionWindow = SDL_CreateWindow("How to Play",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(instructionWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* bgTexture = IMG_LoadTexture(renderer,"image/instruction_bg.png");
    instructionWindowRunning = true;

    SDL_Event event;
    while (instructionWindowRunning) {
        while (SDL_PollEvent(&event)) {
            //Nếu người dùng đóng cửa sổ chính hoặc thoát ứng dụng
            if (event.type == SDL_QUIT) {
                instructionWindowRunning = false;
            }
            //Kiểm tra có phải sự kiện liên quan đến cửa sổ bị đóng không
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) { 
                // Kiểm tra xem cửa sổ bị đóng có phải là cửa sổ hướng dẫn không
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