#include "declare.h"
#include "Init.h"
#include "logic.h"
#include "graphic.h"
#include "game_states.h"
#include "game.h"
#include "destroy.h"

// Hàm kiểm tra va chạm giữa 2 vật
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

// Hàm reset khi người chơi chọn Play again ở chế độ chơi 1 người
void resetFor1PlayerMode() {
        gamestarted = true;
        gameover = false;
        score=0;
        checkhealth=2;
        health=1;
        bird.y = SCREEN_HEIGHT / 2;
        van_toc = 0;
    
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
 
// Hàm reset khi người chơi chọn Play again ở chế độ chơi 2 người   
void resetFor2PlayerMode() {
        gamestarted = true;
        gameover =false;
        winner=0;
        bird1.y = SCREEN_HEIGHT / 2;
        bird2.y = SCREEN_HEIGHT/2;
        van_toc1 = 0;
        van_toc2 = 0;

    
        pipes.clear();
        for (int i = 0; i < 3; i++) {
            int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes.push_back({ SCREEN_WIDTH + i * 300, height });
        }
}

// Hàm reset khi người chơi chọn quay trở lại menu ban đầu 
void resetToMainMenu() {
    //Đặt lại trạng thái trò chơi về ban đầu
        gamestarted = false;
        gameover = false;
        winner=0;
        score=0;
        level=0;
        checkhealth=2;
        health=1;
    //Đặt lại vị trí của chim
        bird.y = SCREEN_HEIGHT / 2;
        bird1.y = SCREEN_HEIGHT / 2;
        bird2.y = SCREEN_HEIGHT / 2;
    //Đặt vận tốc về 0
        van_toc = 0;
        van_toc1 = 0;
        van_toc2 = 0;
    
    //Xóa các đối tượng trong game
        pipes.clear();
        bombs.clear();
        healths.clear();
        playerName1.clear();
        playerName2.clear();

    //Tạo lại các ống, bom và health
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

// Hàm reset khi người chơi có nhiều hơn 1 mạng
void resetwhileplay () {
    gamestarted = true;
    gameover = false;
    bird.y = SCREEN_HEIGHT / 2;
    van_toc = 0;

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