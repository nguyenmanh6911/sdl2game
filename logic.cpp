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
        checkhealth=2;
        health=1;
        bird.y = SCREEN_HEIGHT / 2;
        van_toc = 0;
        TOC_DO_DICH_CHUYEN_CUA_ONG=5;
    
        pipes.clear();
        bombs.clear();
        healths.clear();

        for (int i = 0; i < 3; i++) {
            int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes.push_back({ SCREEN_WIDTH + i * 400, height });
        }

        for (int i = 0; i < 3; i++) {
            int x = (SCREEN_WIDTH - 200) + i * 400 - CHIEU_RONG_BOM / 2; 
            int margin = 15;
            int heightRef = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50; 
            int minY = heightRef + margin;
            int maxY = minY + KHOANG_CACH_GIUA_HAI_ONG - CHIEU_DAI_BOM - 2 * margin;
            int y = minY + rand() % (maxY - minY);
            bombs.push_back({x, y});
            
        }

        healths.push_back({SCREEN_WIDTH + 700, rand() % (500) + 100, false});
        healths.push_back({SCREEN_WIDTH + 3800, rand() % (500) + 100, false});
    
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

void reset2() {
        gamestarted = false;
        gameover = false;
        score=0;
        level=0;
        bird.y = SCREEN_HEIGHT / 2;
        van_toc = 0;
        TOC_DO_DICH_CHUYEN_CUA_ONG=5;
    
        pipes.clear();
        for (int i = 0; i < 3; i++) {
            int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes.push_back({ SCREEN_WIDTH + i * 300, height });
        }
}

void resetwhileplay () {
    gamestarted = true;
    gameover = false;
    bird.y = SCREEN_HEIGHT / 2;
    van_toc = 0;
    TOC_DO_DICH_CHUYEN_CUA_ONG=5;

    pipes.clear();
    bombs.clear();
    healths.clear();

    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({ SCREEN_WIDTH + i * 400, height });
    }

    for (int i = 0; i < 3; i++) {
        int x = (SCREEN_WIDTH - 200) + i * 400 - CHIEU_RONG_BOM / 2; 
        int margin = 15;
        int heightRef = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50; 
        int minY = heightRef + margin;
        int maxY = minY + KHOANG_CACH_GIUA_HAI_ONG - CHIEU_DAI_BOM - 2 * margin;
        int y = minY + rand() % (maxY - minY);
        bombs.push_back({x, y});
        
    }
}