#include "declare.h"
#include "Init.h"
#include "game.h"
#include "graphic.h"
#include "reset.h"
#include "game_states.h"
#include "collision.h"
#include "render_in_game.h"
#include "ranking.h"
#include "destroy.h"

// Xử lý sự kiện tắt, nhấn phím hoặc chuột ở chế độ 1 người chơi
void handle_event() {
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

}

// Xử lý sự kiện tắt, nhấn phím hoặc chuột ở chế độ 2 người chơi
void handle_event_mode2 () {
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
}

//Cập nhật toạ độ chim ở chế độ 1 người chơi
void capnhat_toado_bird () {
    van_toc += TRONGLUC;
    bird.y += van_toc;
}

//Cập nhật toạ độ chim ở chế độ 2 người chơi
void capnhat_toado_bird_mode2 () {
    van_toc1 += TRONGLUC;
    van_toc2 += TRONGLUC;
    bird1.y += van_toc1;
    bird2.y += van_toc2;
}

// Lấy điểm cao nhất level đang chơi
void update_maxscore () {
    if (!gothighestscore) {
        highestscore = get_highest_score(level); 
        gothighestscore=true;
    }
}

// Lưu điểm hiện tại và sắp xếp lại file ranking
void sapxep_rankings () {
    if (gameover) {
        saveScore(playerName1, score, level);
        saveTop5Scores(level);               
    }
}


// Gọi hàm khi người chơi chọn level 1
void Game_Level1() {
    update_maxscore(); //Cập nhật điểm cao nhất
    
    handle_event(); // Xử lí sự kiện

    capnhat_toado_bird(); 

    xuliPipe(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_1); 

    xulivacham_screen(); 

    sapxep_rankings(); //Lưu điểm hiện tại và sắp xếp lại file ranking

    render_level1(); //Render ra màn hình

    reset_frame(); //Reset lại khung hình
}

//Gọi hàm khi người chơi chọn level 2
void Game_Level2() {
    update_maxscore();

    handle_event(); // Xử lý sự kiện nhấn phím hoặc chuột
    
    capnhat_toado_bird();// Cập nhật toạ độ chim

    xuliPipe(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2); 

    xuliBomb(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2); 

    xuliHealth(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_2);

    xulivacham_screen(); 
    
    sapxep_rankings(); 
    
    render_level2_3();
    reset_frame();
}

// Gọi hàm khi người chơi chọn level 3
void Game_Level3() {
    update_maxscore();

    handle_event(); 
    
    capnhat_toado_bird();

    xuliPipe(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3); 

    xuliBomb(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3); 

    xuliHealth(TOC_DO_DICH_CHUYEN_CUA_ONG_LEVEL_3); 

    xulivacham_screen(); 

    sapxep_rankings(); 

    render_level2_3(); 

    reset_frame();
}

void Mode2Player() {
    handle_event_mode2();

    capnhat_toado_bird_mode2();

    xuliPipe_mode2(TOC_DO_DICH_CHUYEN_CUA_ONG_MODE_2);

    xulivacham_screen_mode2();
   
    render_mode2();
}
