#include "declare.h"
#include "Init.h"
#include "game_states.h"
#include "graphic.h"
#include "logic.h"
#include "game.h"   
#include "destroy.h"
#include "instruction.h"

void countdown() {
    for (int i = 3; i > 0; i--) {
        SDL_RenderClear(renderer);

        string countdownText = to_string(i);
        SDL_Rect countdownRect = {450, 300, 100, 100};
        SDL_Texture* countdownTexture = NULL;
        updateScoreTexture( countdownText, countdownTexture, countdownRect);

        if (countdownTexture) {
            SDL_RenderCopy(renderer, countdownTexture, NULL, &countdownRect);
            SDL_DestroyTexture(countdownTexture);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    SDL_RenderClear(renderer);

    SDL_Texture* goTexture = IMG_LoadTexture(renderer,"hwg11.png");
    SDL_Rect goRect = {132, 130, 736, 490};

    renderTexture(goTexture,goRect);

    SDL_RenderPresent(renderer);
    SDL_Delay(1500);
}

void beforeGameStarted() {
    bool checksound = 1;

    while (gamestarted == false && running == true) {
        SDL_RenderClear(renderer);

        SDL_Rect firstbg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, backgroundTexture1, NULL, &firstbg);

        loadtext("UncialAntiqua-Regular.ttf",60,red,"Flappy Bird",flappybirdrect);
        loadtext("Arial.ttf", 40, red, "1 Player", mode1);
        loadtext("Arial.ttf", 40, red, "2 Player", mode2);
        loadtext("Arial.ttf", 40, red, "Instruction", instructionrect);
        loadtext("Arial.ttf", 32, red, "Exit", exit1rect);

        if (checksound == 1) {
            renderTexture(soundimage, soundrect);
        }
        else if (checksound == 0) {
            renderTexture(muteimage, soundrect);
        }

        SDL_RenderPresent(renderer);

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= mode1.x && x <= mode1.x + mode1.w && y >= mode1.y && y <= mode1.y + mode1.h) {
                    gamemode = 1;
                    countdown();
                    gamestarted = true;

                } else if (x >= mode2.x && x <= mode2.x + mode2.w && y >= mode2.y && y <= mode2.y + mode2.h) {
                    gamemode = 2;
                    countdown();
                    gamestarted = true;
                }else if (x >= instructionrect.x && x <= instructionrect.x + instructionrect.w && y >= instructionrect.y && y <= instructionrect.y + instructionrect.h) {
                    std::thread instructionThread(showInstructionWindow);
                    instructionThread.detach();
                 }
                else if (x >= soundrect.x && x <= soundrect.x + soundrect.w && y >= soundrect.y && y <= soundrect.y + soundrect.h) {
                    if (Mix_PlayingMusic()==0 && checksound==0) {
                        Mix_PlayMusic(music,-1);
                        checksound=1;
                    } else if (Mix_PlayingMusic()==1 && checksound==1){
                         Mix_HaltMusic();
                        checksound=0;
                    }

                }
                else if (x >= exit1rect.x && x <= exit1rect.x + exit1rect.w && y >= exit1rect.y && y <= exit1rect.y + exit1rect.h) {
                    running = false;
                }
            }
        }
    }
}

void ayready() {

    SDL_RenderClear(renderer);

    SDL_Texture* goTexture = IMG_LoadTexture(renderer,"hwga1.png");
    SDL_Rect goRect = {218, 93, 564, 564};

    renderTexture(goTexture,goRect);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_RenderClear(renderer);

    SDL_Texture* readyTexture = IMG_LoadTexture(renderer,"ready1.png");
    SDL_Rect readyRect = {250, 125, 500, 500};
    renderTexture(readyTexture,readyRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(2000);
}

void GameOver() {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("UncialAntiqua-Regular.ttf", 60, red, "Game Over", gameoverrect);
    loadtext("Arial.ttf", 32, red, "Play again", playagainrect1);
    loadtext("Arial.ttf", 32, red, "Exit", exit2rect);
    loadtext("arial.ttf", 26, red, scoreText.c_str(), scorerect1);

    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool waiting = true;
    while (waiting) { 
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                waiting = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= playagainrect.x && x <= playagainrect.x + playagainrect.w && y >= playagainrect.y && y <= playagainrect.y + playagainrect.h) {
                    ayready();
                    reset();
                    waiting = false;
                }
                else if (x >= exit2rect.x && x <= exit2rect.x + exit2rect.w && y >= exit2rect.y && y <= exit2rect.y + exit2rect.h) {
                    running = false;
                    waiting = false;
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) { 
                gamestarted = false;
                gameover = false;
                waiting = false;
            }
        }
    }
}


void GameOver1() {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("Arial.ttf", 60, red, "Player 1 win", gameoverrect);
    loadtext("Arial.ttf", 32, red, "Play again", playagainrect);
    loadtext("Arial.ttf", 32, red, "Exit", exit2rect);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool waiting = true;

    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                waiting = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= playagainrect.x && x <= playagainrect.x + playagainrect.w &&y >= playagainrect.y && y <= playagainrect.y + playagainrect.h) {
                    ayready();
                    reset1();
                    waiting = false;
                }
                else if (x >= exit2rect.x && x <= exit2rect.x + exit2rect.w&&y >= exit2rect.y && y <= exit2rect.y + exit2rect.h) {
                    running = false;
                    waiting = false;
                }
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_m) {
                    gamestarted = false;
                    gameover = false;
                    waiting = false;
                }
            }
        }
    }
}

void GameOver2() {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("Arial.ttf", 60, red, "Player 2 win", gameoverrect);
    loadtext("Arial.ttf", 32, red, "Play again", playagainrect);
    loadtext("Arial.ttf", 32, red, "Exit", exit2rect);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    bool waiting = true;

    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                waiting = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= playagainrect.x && x <= playagainrect.x + playagainrect.w &&y >= playagainrect.y && y <= playagainrect.y + playagainrect.h) {
                    ayready();
                    reset1();
                    waiting = false;
                }
                else if (x >= exit2rect.x && x <= exit2rect.x + exit2rect.w&&y >= exit2rect.y && y <= exit2rect.y + exit2rect.h) {
                    running = false;
                    waiting = false;
                }
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_m) {
                    gamestarted = false;
                    gameover = false;
                    waiting = false;
                }
            }
        }
    }
}