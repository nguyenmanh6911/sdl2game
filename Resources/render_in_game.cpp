#include "declare.h"
#include "Init.h"
#include "render_in_game.h"
#include "graphic.h"


void render_level1() {
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

    SDL_RenderCopy(renderer, heart1, NULL, &heartrect1);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
}

void render_level2_3() {
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
    
    if (health==1) SDL_RenderCopy(renderer, heart1, NULL, &heartrect1);
    else if (health==2) SDL_RenderCopy(renderer, heart2, NULL, &heartrect2);
    else if (health==3) SDL_RenderCopy(renderer, heart3, NULL, &heartrect3);
    
    if (scoreTexture) SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);
    if (highestscoreTexture) SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);

    SDL_RenderPresent(renderer);
    SDL_Delay(8);
}

void render_mode2 () {
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