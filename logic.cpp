#include "declare.h"
#include "Init.h"
#include "logic.h"
#include "graphic.h"
#include "game_states.h"
#include "game.h"
#include "destroy.h"


bool checkvacham(SDL_Rect a, SDL_Rect b) {
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }
    return true;
}

void reset() {
        gamestarted = true;
        gameover = false;
        score=0;
        bird.y = SCREEN_HEIGHT / 2;
        van_toc = 0;
        TOC_DO_DICH_CHUYEN_CUA_ONG=5;
    
        pipes.clear();
        for (int i = 0; i < 3; i++) {
            int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes.push_back({ SCREEN_WIDTH + i * 300, height });
        }
    }
    
    void reset1() {
        gamestarted = true;
        gameover =false;
        winner=0;
        bird1.y = SCREEN_HEIGHT / 2;
        bird2.y = SCREEN_HEIGHT/2;
        van_toc1 = 0;
        van_toc2 = 0;
        TOC_DO_DICH_CHUYEN_CUA_ONG=5;
    
        pipes.clear();
        for (int i = 0; i < 3; i++) {
            int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes.push_back({ SCREEN_WIDTH + i * 300, height });
        }
    }
    