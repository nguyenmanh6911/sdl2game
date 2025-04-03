#include "declare.h"


SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;
TTF_Font* font1=NULL;
Mix_Music* music=NULL;
Mix_Chunk* soundflap=NULL;
Mix_Chunk *soundvacham=NULL;
Mix_Chunk *soundting_ting=NULL;
Mix_Chunk *explode = NULL;
SDL_Texture* backgroundTexture=NULL;
SDL_Texture *birdTexture=NULL;
SDL_Texture* birdTexture1=NULL;
SDL_Texture* birdTexture2=NULL;
SDL_Texture *pipeTexture=NULL;
SDL_Texture* bombTexture = NULL;
SDL_Texture *healthTexture=NULL;
SDL_Texture *backgroundTexture1=NULL;
SDL_Texture *backgroundTexture2=NULL;
SDL_Texture* soundimage=NULL;
SDL_Texture *muteimage=NULL;
SDL_Texture* rankimage=NULL;
SDL_Texture* scoreTexture = NULL;
SDL_Texture *highestscoreTexture = NULL;
SDL_Texture* homeimage = NULL;
SDL_Texture *returnimage = NULL;
SDL_Texture* heart1 = NULL;
SDL_Texture* heart2 = NULL;
SDL_Texture* heart3 = NULL;
atomic<bool> instructionWindowRunning(false);

SDL_Color red = {255, 0, 0};
SDL_Color white = {255, 255, 255};
SDL_Color purple = {203, 108, 230};

bool running = true;
bool gamestarted = false;
bool gameover = false;
bool checksound = true;
bool instructionOpen = false;
bool exitpressed = false;
bool selected = false;
bool gothighestscore = false;
int bgPosition = 0;
int frame = 0;
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
string playerName1="";
string playerName2="";

SDL_Rect bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect bird1 = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect bird2 = {100 - CHIEU_RONG_KHUNG_HINH, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect flappybirdrect = {280, 50, 450, 150};
SDL_Rect Startrect = {375, 250,250, 120};
SDL_Rect instructionrect = {390, 370, 372, 88};
SDL_Rect exit1rect = {450, 490, 151, 92};
SDL_Rect playagainrect = {340, 300, 325, 100};
SDL_Rect playagainrect1 = {318,350, 325, 100};
SDL_Rect exit2rect = {440,500, 200, 75};
SDL_Rect gameoverrect = {230,50,500,200};
SDL_Rect soundrect = {25, 25, 80,80};
SDL_Rect scorerect = {750, 50, 50, 50};
SDL_Rect scorerect1 ={350,220,325,100};
SDL_Rect highestscorerect = {750,125,50,50};
SDL_Rect winnerect = {230,80,630,160};
SDL_Rect mode1 = {300, 250, 230, 83};
SDL_Rect mode2 = {500, 250, 230, 78};
SDL_Rect homerect = {10, 10, 60, 60};
SDL_Rect bombrect = {0, 0, 0, 0};
SDL_Rect healthrect = {0 ,0, 0, 0};
SDL_Rect returnrect = {SCREEN_WIDTH-120,SCREEN_HEIGHT/2-40, 80,80};
SDL_Rect rankrect = {SCREEN_WIDTH-80, 0, 80,80};
SDL_Rect heartrect1 = {0, 0, 400, 125};
SDL_Rect heartrect2 = {0, 0, 400, 125};
SDL_Rect heartrect3 = {0, 0, 400, 125};

string scoreText = "Score: " ;
string highestscoreText = "Highest score: ";

SDL_Rect animation[SO_KHUNG_HINH];

vector <Pipe> pipes;
vector <Bomb> bombs;
vector <Health> healths;