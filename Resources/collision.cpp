#include "collision.h"
#include "declare.h" 
#include "Init.h"

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

void xulivacham_screen() {
    if ((bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0)&& !gameover) {
        health--;
        Mix_PlayChannel(-1,soundvacham, 0);
        if (health == 0) {
            gameover = true;
        } else {
            resetwhileplay();
        }
    }
}

void xuliPipe(int toc_do) {
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= toc_do;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes[i].pass = false;
        }

        if (pipes[i].pass == false && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, soundting_ting, 0);
            pipes[i].pass = true;
            highestscore = max(score, highestscore);
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };

        if (checkvacham(bird, Ong_tren) || checkvacham(bird, Ong_duoi)&& !gameover) {
           Mix_PlayChannel(-1, soundvacham, 0);
            health--;
            if (health == 0) {
                gameover = true;
            } else {
                resetwhileplay(); // Hàm reset khi số health > 0
            }
        }
    }
}

void xuliPipe_mode2(int toc_do) {
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_MODE_2;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes[i].pass = false;
        }

        if (!pipes[i].pass && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, soundting_ting, 0);
            pipes[i].pass = true;
            highestscore = max(score, highestscore);
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG};

        // Kiểm tra va chạm, xác định người thắng
        if (checkvacham(bird1, Ong_tren) || checkvacham(bird1, Ong_duoi)) {
            Mix_PlayChannel(-1, soundvacham, 0);
            gameover = true;
            winner = 2;
            break;
        }

        if (checkvacham(bird2, Ong_tren) || checkvacham(bird2, Ong_duoi)) {
            Mix_PlayChannel(-1, soundvacham, 0);
            gameover = true;
            winner = 1;
            break;
        }
    }
}

void xuliBomb(int toc_do) {
    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].x -= toc_do;
        
        if (bombs[i].x + CHIEU_RONG_BOM < 0) {
            int toadobombmax = bombs[0].x;
            for (int j = 1; j < bombs.size(); j++) {
                if (bombs[j].x > toadobombmax) {
                    toadobombmax = bombs[j].x; // Tìm toạ độ bomb ở ngoài cùng
                }
            }

            int x = toadobombmax + 400 - CHIEU_RONG_BOM / 2;
            bombs[i].x = x; // Đặt lại toạ độ quả bomb vừa ra khỏi màn hình
           
            int cachong = 15;
            int heightRef = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50; // Chọn chiều cao ngẫu nhiên cho ống trên
            int minY = heightRef + cachong; // Vị trí tối thiểu mà bom có thể xuất hiện
            int maxY = minY + KHOANG_CACH_GIUA_HAI_ONG- CHIEU_DAI_BOM - 2 * cachong;// Vị trí tối đa mà bom có thể xuất hiện
    
            bombs[i].y = minY + rand() % (maxY - minY);
        }

        SDL_Rect bombrect = {bombs[i].x, bombs[i].y, 50, 50};
    
        if (checkvacham(bird, bombrect)&& !gameover) {
            health--;
           Mix_PlayChannel(-1, soundvacham, 0);
           if (health == 0) {
            gameover = true;
        } else {
           resetwhileplay();
        }
        }
    }
}

void xuliHealth (int toc_do) {
    if (checkhealth!=0) {
        for (int i = 0; i < healths.size(); i++) {
            healths[i].x -= toc_do;

            if (healths[i].x + CHIEU_RONG_HEALTH < 0) {
                checkhealth--;
                healths[i].cham = false;
            }

            healthrect = { healths[i].x, healths[i].y, CHIEU_RONG_HEALTH, CHIEU_DAI_HEALTH };

            if (healths[i].cham == false && checkvacham(bird, healthrect)) {
                Mix_PlayChannel(-1, soundting_ting, 0);
                health++;
                healths[i].cham = true;
                healths[i].x = -100;
            }
    }
    }
}

void xulivacham_screen_mode2() {
    if (bird1.y + bird1.h > SCREEN_HEIGHT || bird1.y < 0) {
        Mix_PlayChannel(-1, soundvacham, 0);
         gameover = true;
         winner = 2;
     }
 
     if (bird2.y + bird2.h > SCREEN_HEIGHT || bird2.y < 0) {
         Mix_PlayChannel(-1, soundvacham, 0);
         gameover = true;
         winner = 1;
     }
}