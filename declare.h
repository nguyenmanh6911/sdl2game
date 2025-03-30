#ifndef DECLARE_H
#define DECLARE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>
#include <string>

using namespace std;

constexpr const int SCREEN_WIDTH = 1000;
constexpr const int SCREEN_HEIGHT=750;
constexpr const int CHIEU_RONG_KHUNG_HINH=48;
constexpr const int CHIEU_DAI_KHUNG_HINH=36;
constexpr const int TRONGLUC = 1;
constexpr const int LUC_NHAY = -15;
constexpr const int CHIEU_RONG_ONG = 100;
constexpr const int KHOANG_CACH_GIUA_HAI_ONG = 200;
constexpr const int KHOANG_CACH_GIUA_HAI_ONG1 =250;
constexpr const int CHIEU_DAI_BOM = 40;
constexpr const int CHIEU_RONG_BOM = 40;
constexpr const int CHIEU_RONG_HEALTH =50;
constexpr const int CHIEU_DAI_HEALTH =50;
extern int TOC_DO_DICH_CHUYEN_CUA_ONG;
constexpr const int TOC_DO_DICH_CHUYEN_CUA_MAN = 2;
constexpr const int TOC_DO_DICH_CHUYEN_CUA_ONG1 = 4;
constexpr const int TOC_DO_DICH_CHUYEN_CUA_ONG3 = 7;
constexpr const int SO_KHUNG_HINH = 3;
constexpr const int SO_KHUNG_HINH1 = 4;
constexpr const char* WINDOW_TITLE = "Flappy Bird";

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font;
extern TTF_Font* font1;
extern Mix_Music* music;
extern Mix_Chunk* effect1;
extern Mix_Chunk *effect2;
extern Mix_Chunk *effect3;
extern SDL_Texture* backgroundTexture;
extern SDL_Texture *birdTexture;
extern SDL_Texture* birdTexture1;
extern SDL_Texture* birdTexture2;
extern SDL_Texture *pipeTexture;
extern SDL_Texture* bombTexture;
extern SDL_Texture* healthTexture;
extern SDL_Texture *backgroundTexture1;
extern SDL_Texture* soundimage;
extern SDL_Texture *muteimage;
extern SDL_Texture* scoreTexture;
extern SDL_Texture *highestscoreTexture;
extern SDL_Texture* homeimage;
extern SDL_Texture* heart1;
extern SDL_Texture* heart2;
extern SDL_Texture* heart3;
extern atomic<bool> instructionWindowRunning;

extern SDL_Color red;
extern SDL_Color white;

extern bool running;
extern bool gamestarted;
extern bool gameover;
extern int bgPosition;
extern int frame;
extern int frame1;
extern int score;
extern int highestscore;
extern int van_toc;
extern int gamemode;
extern int winner;
extern int van_toc1;
extern int van_toc2;
extern int level;
extern int health;
extern int checkhealth;
extern SDL_Rect bird1;
extern SDL_Rect bird2;


extern SDL_Rect bird;
extern SDL_Rect flappybirdrect;
extern SDL_Rect Startrect;
extern SDL_Rect instructionrect;
extern SDL_Rect exit1rect;
extern SDL_Rect textrect4 ;
extern SDL_Rect playagainrect;
extern SDL_Rect playagainrect1;
extern SDL_Rect exit2rect;
extern SDL_Rect gameoverrect;
extern SDL_Rect soundrect;
extern SDL_Rect scorerect;
extern SDL_Rect scorerect1;
extern SDL_Rect mode1;
extern SDL_Rect mode2;
extern SDL_Rect highestscorerect;
extern SDL_Rect homerect;
extern SDL_Rect bombrect;
extern SDL_Rect healthrect;
extern SDL_Rect heartrect1;
extern SDL_Rect heartrect2;
extern SDL_Rect heartrect3;

extern SDL_Rect animation[SO_KHUNG_HINH];
extern SDL_Rect animation1[SO_KHUNG_HINH1];

extern string scoreText;
extern string highestscoreText;

struct Pipe {
    int x, height;
    bool pass;
};

struct Bomb {
    int x, y;
};

struct Health {
    int x, y;
    bool cham;
};

extern vector <Pipe> pipes;
extern vector <Bomb> bombs;
extern vector <Health> healths;


#endif
