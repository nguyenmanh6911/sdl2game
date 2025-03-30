#include "declare.h"

int TOC_DO_DICH_CHUYEN_CUA_ONG=5;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;
TTF_Font* font1=NULL;
Mix_Music* music=NULL;
Mix_Chunk* effect1=NULL;
Mix_Chunk *effect2=NULL;
Mix_Chunk *effect3=NULL;
SDL_Texture* backgroundTexture=NULL;
SDL_Texture *birdTexture=NULL;
SDL_Texture* birdTexture1=NULL;
SDL_Texture* birdTexture2=NULL;
SDL_Texture *pipeTexture=NULL;
SDL_Texture* bombTexture = NULL;
SDL_Texture *healthTexture=NULL;
SDL_Texture *backgroundTexture1=NULL;
SDL_Texture* soundimage=NULL;
SDL_Texture *muteimage=NULL;
SDL_Texture* scoreTexture = NULL;
SDL_Texture *highestscoreTexture = NULL;
SDL_Texture* homeimage = NULL;
SDL_Texture* heart1 = NULL;
SDL_Texture* heart2 = NULL;
SDL_Texture* heart3 = NULL;
atomic<bool> instructionWindowRunning(false);

SDL_Color red = {255, 0, 0};
SDL_Color white = {255, 255, 255};

bool running = true;
bool gamestarted = false;
bool gameover = false;
int bgPosition = 0;
int frame = 0;
int frame1=0;
int score = 0;
int highestscore = 0;
int van_toc=0;
int gamemode=1;
int winner=0;
int van_toc1 = 0;
int van_toc2 = 0;
int level=0;
int health=1;
int checkhealth=2;

SDL_Rect bird1 = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect bird2 = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect flappybirdrect = {280, 50, 450, 150};
SDL_Rect Startrect = {375, 250,250, 120};
SDL_Rect instructionrect = {355, 400, 300, 120};
SDL_Rect exit1rect = {410, 550, 175, 75};
SDL_Rect textrect4 = {350, 50, 300, 100};
SDL_Rect playagainrect = {350, 300, 325, 100};
SDL_Rect playagainrect1 = {350, 350, 325, 100};
SDL_Rect exit2rect = {400, 500, 200, 75};
SDL_Rect gameoverrect = {275,25,500,200};
SDL_Rect soundrect = {25, 25, 60, 60};
SDL_Rect scorerect = {675, 75, 50, 50};
SDL_Rect scorerect1 ={350,220,325,100};
SDL_Rect mode1 = {225, 250,250, 120};
SDL_Rect mode2 = {535, 250,250, 120};
SDL_Rect highestscorerect = {675,150,50,50};
SDL_Rect homerect = {25, 25, 45, 45};
SDL_Rect bombrect = {0, 0, 0, 0};
SDL_Rect healthrect = {0 ,0, 0, 0};
SDL_Rect heartrect1 = {0, 0, 400, 125};
SDL_Rect heartrect2 = {0, 0, 400, 125};
SDL_Rect heartrect3 = {0, 0, 400, 125};

string scoreText = "Score: " ;
string highestscoreText = "Highest score: ";

SDL_Rect animation[SO_KHUNG_HINH];
SDL_Rect animation1[SO_KHUNG_HINH1];

vector <Pipe> pipes;
vector <Bomb> bombs;
vector <Health> healths;