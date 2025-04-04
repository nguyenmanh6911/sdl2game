#include "declare.h"
#include "Init.h"
#include "game_states.h"
#include "graphic.h"
#include "reset.h"
#include "game.h"   
#include "entername.h"
#include "destroy.h"
#include "ranking.h"
#include "instruction.h"

// Hàm đếm ngược
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

    SDL_Texture* goTexture = IMG_LoadTexture(renderer,"image/hwg11.png");
    SDL_Rect goRect = {132, 130, 736, 490};

    renderTexture(goTexture,goRect);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

// Hàm chọn cấp độ
void chooselevel() {
    SDL_Texture* levelMenuTexture = IMG_LoadTexture(renderer, "image/choose_level.png");

    SDL_Rect level1Rect = { 320, 250, 387, 95 };
    SDL_Rect level2Rect = { 320, 370, 387, 95 };
    SDL_Rect level3Rect = { 320, 490, 387, 95 };

    bool choosing = true;
    SDL_Event event;

    while (choosing) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                choosing = false;
            }
            //Xử lí sự kiện nhấn chuột 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= level1Rect.x && x <= level1Rect.x + level1Rect.w && y >= level1Rect.y && y <= level1Rect.y + level1Rect.h) {
                    level = 1;
                    choosing = false;
                }
                else if (x >= level2Rect.x && x <= level2Rect.x + level2Rect.w && y >= level2Rect.y && y <= level2Rect.y + level2Rect.h) {
                    level = 2;
                    choosing = false;
                }
                else if (x >= level3Rect.x && x <= level3Rect.x + level3Rect.w && y >= level3Rect.y && y <= level3Rect.y + level3Rect.h) {
                    level = 3;
                    choosing = false;
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, levelMenuTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(levelMenuTexture);
}

// Hàm chặn input 
void blockInputFor(int milliseconds) {
    Uint32 start = SDL_GetTicks(); // Lưu lại thời điểm bắt đầu
    SDL_Event event;

    // Vòng lặp chạy đến khi hết thời gian truyền vào
    while (SDL_GetTicks() - start < milliseconds) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return;
            }
        }
        SDL_PumpEvents(); // Cập nhật trạng thái đầu vào để tránh treo chương trình

        // Xóa các sự kiện nhấn phím và chuột
        SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
        SDL_FlushEvent(SDL_KEYDOWN);
    }
}


// Hàm hiển thị giao diện trước khi bắt đầu trò chơi
void beforeGameStarted() {
    //Đặt các biến về mặc định
    instructionOpen = false;
    exitpressed = false;
    mode_selected = false;

    while (gamestarted == false && running == true) {
        SDL_RenderClear(renderer);
        SDL_Rect firstbg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, backgroundTexture1, NULL, &firstbg);

        //Bật/tắt âm thanh
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
                if ((x >= mode1.x && x <= mode1.x + mode1.w && y >= mode1.y && y <= mode1.y + mode1.h) && mode_selected == false) {
                    // Đánh dấu màn hình hướng dẫn và các tùy chọn đã được chọn
                    instructionOpen=true;
                    exitpressed = true;
                    mode_selected = true;
                    gamemode = 1;
                    enterName(playerName1, playerName2, gamemode);
                    if (!running) return;
                    chooselevel();
                    if (!running) return;
                    countdown();
                    gamestarted = true;

                } else if ((x >= mode2.x && x <= mode2.x + mode2.w && y >= mode2.y && y <= mode2.y + mode2.h)&& mode_selected == false) {
                    // Đánh dấu màn hình hướng dẫn và các tùy chọn đã được chọn
                    instructionOpen = true;
                    exitpressed = true;
                    mode_selected = true;
                    gamemode = 2;
                    enterName(playerName1, playerName2, gamemode);
                    if (!running) return; 
                    countdown();
                    gamestarted = true;
                }else if (x >= instructionrect.x && x <= instructionrect.x + instructionrect.w && y >= instructionrect.y && y <= instructionrect.y + instructionrect.h) {
                    if (!instructionOpen) {
                        thread instructionThread(showInstructionWindow);
                        instructionThread.detach();
                    }
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
                    if (!exitpressed) {
                        running = false;
                    }
                }
            }
        }
    }
}

// Hàm render ảnh khi chọn play again
void ayready() {
    SDL_RenderClear(renderer);
    SDL_RenderClear(renderer);

    SDL_Texture* readyTexture = IMG_LoadTexture(renderer,"image/ready1.png");
    SDL_Rect readyRect = {250, 125, 500, 500};
    renderTexture(readyTexture,readyRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
}

// Hàm được gọi khi người chơi thua ở chế độ chơi 1 người
void GameOverFor1PlayerMode(int level) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture2, NULL, &bgRect1);

    //Load chữ
    loadtext_Realsize(renderer, "font/UncialAntiqua-Regular.ttf", 100, red, "Game Over", 210, 50);
    loadtext_Realsize(renderer, "font/Arial.ttf", 80, red, "Play again", 318, 350); 
    loadtext_Realsize(renderer, "font/Arial.ttf", 80, red, "Exit", 420, 500); 
    loadtext_Realsize(renderer, "font/arial.ttf", 70, red, scoreText.c_str(), 350, 220); 

    renderTexture(homeimage, homerect);
    renderTexture(rankimage, rankrect);

    SDL_RenderPresent(renderer);

    blockInputFor(1000); // Chặn input trong 1 giây

    bool waiting = true;
    bool showRanking = false; // Biến để kiểm soát hiển thị Ranking

    SDL_Event event;
    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                waiting = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= playagainrect1.x && x <= playagainrect1.x + playagainrect1.w && y >= playagainrect1.y && y <= playagainrect1.y + playagainrect1.h) {
                    if(!playagain_pressed) {
                    ayready();
                    resetFor1PlayerMode();
                    waiting = false;
                    }
                }
                else if (x >= exit2rect.x && x <= exit2rect.x + exit2rect.w && y >= exit2rect.y && y <= exit2rect.y + exit2rect.h) {
                    if (!exit2pressed){
                    running = false;
                    waiting = false;
                    }
                }
                else if (x >= homerect.x && x <= homerect.x + homerect.w && y >= homerect.y && y <= homerect.y + homerect.h) {
                    resetToMainMenu();
                    waiting = false;
                }
                else if (x >= rankrect.x && x <= rankrect.x + rankrect.w && y >= rankrect.y && y <= rankrect.y + rankrect.h) {
                    playagain_pressed=true;
                    exit2pressed=true;
                    showRanking=true; // Chuyển sang hiển thị Ranking
                }
                else if ((x >= returnrect.x && x <= returnrect.x + returnrect.w && y >= returnrect.y && y <= returnrect.y + returnrect.h )&& showRanking) {
                    playagain_pressed=false;
                    exit2pressed=false;
                    showRanking=false; // Quay lại màn hình Game Over
                }
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_m) { 
                    resetToMainMenu();
                    waiting = false;
                } 
                else if (event.key.keysym.sym == SDLK_r && !showRanking) { 
                    playagain_pressed=true;
                    exit2pressed=true;
                    showRanking = true; // Chuyển sang hiển thị Ranking
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE && showRanking) {
                    playagain_pressed=false;
                    exit2pressed=false;
                    showRanking = false; // Quay lại màn hình Game Over
                }
            }
        }

        SDL_RenderClear(renderer);
        if (showRanking) {
            show_ranking(level); // Hàm hiển thị rank tương ứng với level
        } else {
            // Hiển thị màn hình Game Over
            SDL_RenderCopy(renderer, backgroundTexture2, NULL, &bgRect1);
            loadtext_Realsize(renderer, "font/UncialAntiqua-Regular.ttf", 100, red, "Game Over", 210, 50);
            loadtext_Realsize(renderer, "font/Arial.ttf", 80, red, "Play again", 318, 350); 
            loadtext_Realsize(renderer, "font/Arial.ttf", 80, red, "Exit", 420, 500); 
            loadtext_Realsize(renderer, "font/arial.ttf", 70, red, scoreText.c_str(), 350, 220); 
            renderTexture(homeimage, homerect);
            renderTexture(rankimage, rankrect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}

// Hàm được gọi khi người chơi thắng ở chế độ chơi 2 người
void GameOverFor2PlayerMode(int winner) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture2, NULL, &bgRect1);
    
    //Cập nhật tên người chơi
    string winnertext1 = playerName1 + " wins!";
    string winnertext2 = playerName2 + " wins!";
    const char* winnerText ="";
    if (winner == 1) winnerText = winnertext1.c_str();
    else winnerText= winnertext2.c_str();

    //Load chữ
    loadtext ("font/Arial.ttf",80,red,winnerText,winnerect);
    loadtext_Realsize(renderer,"font/Arial.ttf", 80, red, "Play again", 340,300);
    loadtext_Realsize(renderer,"font/Arial.ttf", 80, red, "Exit", 450, 450);
    renderTexture(homeimage, homerect);
    SDL_RenderPresent(renderer);
    
    blockInputFor(1000);
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
                    resetFor2PlayerMode();
                    waiting = false;
                }
                else if (x >= exit2rect.x && x <= exit2rect.x + exit2rect.w && y >= exit2rect.y && y <= exit2rect.y + exit2rect.h) {
                    running = false;
                    waiting = false;
                }
                else if (x >= homerect.x && x <= homerect.x + homerect.w && y >= homerect.y && y <= homerect.y + homerect.h) {
                    resetToMainMenu();
                    waiting = false;
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                resetToMainMenu();
                waiting = false;
            }
        }
    }
}