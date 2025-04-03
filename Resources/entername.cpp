#include "declare.h"
#include "entername.h"
#include "Init.h"
#include "graphic.h"

// Hàm nhập tên
void enterName(string& playerName1, string& playerName2, int& gamemode) {
    bool entering = true;
    SDL_Texture* entername1 = loadTexture("image/nhapten1.png");
    SDL_Texture* entername2 = loadTexture("image/nhapten2.png");
    string inputName;

    SDL_StartTextInput();
    while (entering) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                entering = false;
            }
            if (event.type == SDL_TEXTINPUT) inputName += event.text.text;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !inputName.empty()) inputName.pop_back(); //Xoá chữ
                if (event.key.keysym.sym == SDLK_RETURN && !inputName.empty()) {
                    if (gamemode == 1) {
                        playerName1 = inputName;
                        entering = false;
                    } else if (gamemode == 2 && playerName1.empty()) {
                        playerName1 = inputName;
                        inputName.clear(); // Xóa để nhập tên Player 2
                    } else if (gamemode == 2 && !playerName1.empty()) {
                        playerName2 = inputName;
                        entering = false;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        if (gamemode == 1) {
            renderfullscreen(entername1, 0, 0);
            // Nhập tên người chơi
            loadtext_Realsize (renderer,"font/Arial.ttf", 50, white, inputName.c_str(), 375, 370);
        } else if (gamemode == 2) {
            renderfullscreen(entername2, 0, 0);
            // Nhập tên 2 người chơi
            loadtext_Realsize(renderer,"font/Arial.ttf", 50, white, playerName1.empty() ? inputName.c_str() : playerName1.c_str(), 375, 210);
            loadtext_Realsize(renderer,"font/Arial.ttf", 50, white, playerName1.empty() ? " " : inputName.c_str(), 375, 500);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_StopTextInput();

    SDL_DestroyTexture(entername1);
    SDL_DestroyTexture(entername2);
}