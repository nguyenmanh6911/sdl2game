#include "declare.h"
#include "Init.h"
#include "game.h"
#include "graphic.h"
#include "logic.h"
#include "game_states.h"
#include "ranking.h"
#include "destroy.h"

// Gọi hàm khi người chơi chọn level 1
void Game_Level1() {
    if (!gothighestscore) {
        highestscore = get_highest_score(level); // Lấy điểm cao nhất level đang chơi
        gothighestscore=true;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
            (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) {
            Mix_PlayChannel(-1, soundflap, 0);
            van_toc = LUC_NHAY;
        }
    }
    
    // Cập nhật vị trí của chim
    van_toc += TRONGLUC;
    bird.y += van_toc;

    // Xử lí toạ dộ ống và va chạm giữa ống và chim
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_1;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes[i].pass = false;
        }

        if (!pipes[i].pass && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, soundting_ting, 0);
            pipes[i].pass = true;
            if (score > highestscore) {
                highestscore = score;
            }
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };

        if ((checkvacham(bird, Ong_tren) || checkvacham(bird, Ong_duoi)) && !gameover) {
            Mix_PlayChannel(-1, soundvacham, 0);
            gameover = true;
        }
    }

    // Kiểm tra va chạm với màn hình
    if ((bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) && !gameover) {
        Mix_PlayChannel(-1, soundvacham, 0);
        gameover = true;
    }

    if (gameover) {
        saveScore(playerName1, score, level); // Lưu điểm hiện tại
        saveTop5Scores(level);                // Sắp xếp lại file ranking
    }

    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    // Cập nhật và hiển thị điểm só
    scoreText = "Score: " + to_string(score);
    highestscoreText = "Highest score: " + to_string(highestscore);

    updateScoreTexture(scoreText, scoreTexture, scorerect);
    updateScoreTexture(highestscoreText,highestscoreTexture, highestscorerect);

    SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird);

    for (int i = 0; i < pipes.size(); i++) {
        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
    }

    if (scoreTexture)
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);

    if (highestscoreTexture)
        SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
    frame = (frame + 1) % SO_KHUNG_HINH;
    if (frame >= SO_KHUNG_HINH) frame = 0;
}

//Gọi hàm khi người chơi chọn level 2
void Game_Level2() {
    if (!gothighestscore) {
        highestscore = get_highest_score(level); // Lấy điểm cao nhất level đang chơi
        gothighestscore=true;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
            (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) {
            Mix_PlayChannel(-1, soundflap, 0);
            van_toc = LUC_NHAY;
        }
    }

    // Cập nhật toạ độ chim
    van_toc += TRONGLUC;
    bird.y += van_toc;

    // Xử lí toạ độ ống và va chạm giữa ống và chim
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2;

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
    
    //Xử lí toạ độ bomb và va chạm với bomb
    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2;
        
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

    if (checkhealth!=0) {
        for (int i = 0; i < healths.size(); i++) {
            healths[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2;

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

    if ((bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0)&& !gameover) {
        health--;
        Mix_PlayChannel(-1,soundvacham, 0);
        if (health == 0) {
            gameover = true;
        } else {
            resetwhileplay();
        }
    }

    if (gameover) {
        saveScore(playerName1, score, level); // Lưu điểm hiện tại
        saveTop5Scores(level);                // Sắp xếp lại file ranking
    }
    
    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    scoreText = "Score: " + to_string(score);
    highestscoreText = "Highest score: " + to_string(highestscore);

    updateScoreTexture(scoreText, scoreTexture, scorerect);
    updateScoreTexture(highestscoreText,highestscoreTexture, highestscorerect);

    SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird);

    for (int i = 0; i < pipes.size(); i++) {
        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
    }
    
    for (int i = 0; i < bombs.size(); i++) {
        bombrect ={bombs[i].x,bombs[i].y,CHIEU_RONG_BOM,CHIEU_DAI_BOM};
        SDL_RenderCopy(renderer, bombTexture, NULL, &bombrect);
    }

    if (checkhealth!=0) {
        for (int i = 0; i < healths.size(); i++) {
            healthrect = { healths[i].x, healths[i].y, CHIEU_RONG_HEALTH, CHIEU_DAI_HEALTH };
            SDL_RenderCopy(renderer, healthTexture, NULL, &healthrect);
        }
    }
    
    if (health==1) {
        SDL_RenderCopy(renderer, heart1, NULL, &heartrect1);
    } else if (health==2) {
        SDL_RenderCopy(renderer, heart2, NULL, &heartrect2);
    } else if (health==3) {
        SDL_RenderCopy(renderer, heart3, NULL, &heartrect3);
    }
    
    if (scoreTexture) SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);
    if (highestscoreTexture) SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
    frame = (frame + 1) % SO_KHUNG_HINH;
    if (frame >= SO_KHUNG_HINH) frame = 0;
}

// Gọi hàm khi người chơi chọn level 3
void Game_Level3() {
    if (!gothighestscore) {
        highestscore = get_highest_score(level); // Lấy điểm cao nhất level đang chơi
        gothighestscore=true;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
            (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) {
            Mix_PlayChannel(-1, soundflap, 0);
            van_toc = LUC_NHAY;
        }
    }
    
    van_toc += TRONGLUC;
    bird.y += van_toc;

    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG- 100) + 50;
            pipes[i].pass = false;
        }

        if (!pipes[i].pass && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, soundting_ting, 0);
            pipes[i].pass = true;
            highestscore = max(score, highestscore);
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };

        if ((checkvacham(bird, Ong_tren) || checkvacham(bird, Ong_duoi)) && !gameover) {
            Mix_PlayChannel(-1, soundvacham, 0);
            gameover = true;
            health--;
            if (health == 0) {
                gameover = true;
            } else {
                resetwhileplay();
            }
        }
    }

    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3;
        
        if (bombs[i].x + CHIEU_RONG_BOM < 0) {
            int toadobombmax = bombs[0].x;
            for (int j = 1; j < bombs.size(); j++) {
                if (bombs[j].x > toadobombmax) {
                    toadobombmax = bombs[j].x;
                }
            }

            int x = toadobombmax + 400 - CHIEU_RONG_BOM / 2;
            bombs[i].x = x;
           
            int cachong = 15;
            int heightRef = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            int minY = heightRef + cachong;
            int maxY = minY + KHOANG_CACH_GIUA_HAI_ONG - CHIEU_DAI_BOM - 2 * cachong;
    
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

    if (checkhealth!=0) {
        for (int i = 0; i < healths.size(); i++) {
            healths[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3;

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

    if ((bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0)&& !gameover) {
        health--;
        Mix_PlayChannel(-1, soundvacham, 0);
        if (health == 0) {
            gameover = true;
        } else {
            resetwhileplay();
        }
    }

    if (gameover) {
        saveScore(playerName1, score, level); // Lưu điểm hiện tại
        saveTop5Scores(level);                // Sắp xếp lại file ranking
    }

    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    scoreText = "Score: " + to_string(score);
    highestscoreText = "Highest score: " + to_string(highestscore);
    
    updateScoreTexture(scoreText, scoreTexture, scorerect);
    updateScoreTexture(highestscoreText,highestscoreTexture, highestscorerect);

    SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird);

    for (int i = 0; i < pipes.size(); i++) {
        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
    }

    for (int i = 0; i < bombs.size(); i++) {
        bombrect ={bombs[i].x,bombs[i].y,CHIEU_RONG_BOM,CHIEU_DAI_BOM};
        SDL_RenderCopy(renderer, bombTexture, NULL, &bombrect);
    }

    if (checkhealth!=0) {
        for (int i = 0; i < healths.size(); i++) {
            healthrect = { healths[i].x, healths[i].y, CHIEU_RONG_HEALTH, CHIEU_DAI_HEALTH };
            SDL_RenderCopy(renderer, healthTexture, NULL, &healthrect);
        }
    }
    
    if (health==1) {
        SDL_RenderCopy(renderer, heart1, NULL, &heartrect1);
    } else if (health==2) {
        SDL_RenderCopy(renderer, heart2, NULL, &heartrect2);
    } else if (health==3) {
        SDL_RenderCopy(renderer, heart3, NULL, &heartrect3);
    }
    


    if (scoreTexture)
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);

    if (highestscoreTexture)
        SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
    frame = (frame + 1) % SO_KHUNG_HINH;
    if (frame >= SO_KHUNG_HINH) frame = 0;
}

void Mode2Player() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                Mix_PlayChannel(-1, soundflap, 0);
            van_toc1 = LUC_NHAY;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            Mix_PlayChannel(-1, soundflap, 0);
            van_toc2 = LUC_NHAY;
        }
    }

    //Cập nhật toạ độ của 2 con chim
    van_toc1 += TRONGLUC;
    van_toc2 += TRONGLUC;
    bird1.y += van_toc1;
    bird2.y += van_toc2;

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
    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    SDL_RenderCopy(renderer, birdTexture1, NULL, &bird1);
    SDL_RenderCopy(renderer, birdTexture2, NULL, &bird2);

    for (int i = 0; i < pipes.size(); i++) {
        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}
