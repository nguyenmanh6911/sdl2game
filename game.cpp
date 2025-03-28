#include "declare.h"
#include "Init.h"
#include "game.h"
#include "graphic.h"
#include "logic.h"
#include "game_states.h"
#include "destroy.h"

void ingame() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||
            (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) {
            Mix_PlayChannel(-1, effect1, 0);
            van_toc = LUC_NHAY;
        }
    }

    van_toc += TRONGLUC;
    bird.y += van_toc;

    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes[i].pass = false;
        }

        if (!pipes[i].pass && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, effect3, 0);
            pipes[i].pass = true;
            highestscore = max(score, highestscore);

            if (score == 10)
                TOC_DO_DICH_CHUYEN_CUA_ONG++;
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };

        if (checkvacham(bird, Ong_tren) || checkvacham(bird, Ong_duoi)) {
            Mix_PlayChannel(-1, effect2, 0);
            gameover = true;
        }
    }

    if (bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) {
        Mix_PlayChannel(-1, effect2, 0);
        gameover = true;

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

    if (scoreTexture)
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);

    if (highestscoreTexture)
        SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
    frame = (frame + 1) % SO_KHUNG_HINH;
    if (frame >= SO_KHUNG_HINH) frame = 0;
}

void playmode() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                Mix_PlayChannel(-1, effect1, 0);
            van_toc1 = LUC_NHAY;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            Mix_PlayChannel(-1, effect1, 0);
            van_toc2 = LUC_NHAY;
        }
    }

    van_toc1 += TRONGLUC;
    van_toc2 += TRONGLUC;

    bird1.y += van_toc1;
    bird2.y += van_toc2;

    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG;

        if (pipes[i].x + CHIEU_RONG_ONG < 0) {
            pipes[i].x = SCREEN_WIDTH;
            pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
            pipes[i].pass = false;
        }

        if (!pipes[i].pass && bird.x > pipes[i].x + CHIEU_RONG_ONG) {
            score++;
            Mix_PlayChannel(-1, effect3, 0);
            pipes[i].pass = true;
            highestscore = max(score, highestscore);

            if (score == 10)
                TOC_DO_DICH_CHUYEN_CUA_ONG++;
        }

        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };

        if (checkvacham(bird1, Ong_tren) || checkvacham(bird1, Ong_duoi)) {
                Mix_PlayChannel(-1, effect2, 0);
            gameover = true;
            winner = 2;
            break;
        }

        if (checkvacham(bird2, Ong_tren) || checkvacham(bird2, Ong_duoi)) {
             Mix_PlayChannel(-1, effect2, 0);
            gameover = true;
            winner = 1;
            break;
        }
    }

    if (bird1.y + bird1.h > SCREEN_HEIGHT || bird1.y < 0) {
        Mix_PlayChannel(-1, effect2, 0);
        gameover = true;
        winner = 2;
    }

    if (bird2.y + bird2.h > SCREEN_HEIGHT || bird2.y < 0) {
        Mix_PlayChannel(-1, effect2, 0);
        gameover = true;
        winner = 1;
    }
    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    // SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird1);
    // SDL_RenderCopy(renderer, birdTexture1, &animation1[frame1], &bird2);
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

    frame = (frame + 1) % SO_KHUNG_HINH1;
    frame1 = (frame1 + 1) % SO_KHUNG_HINH;
    if (frame >= SO_KHUNG_HINH) frame = 0;
    if (frame1 >= SO_KHUNG_HINH1) frame1 = 0;
}
