#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;
const int TRONGLUC = 1;
const int LUC_NHAY = -15;
const int CHIEU_RONG_ONG = 100;
const int KHOANG_CACH_GIUA_HAI_ONG = 200;
int TOC_DO_DICH_CHUYEN_CUA_ONG = 5;
const int TOC_DO_DICH_CHUYEN_CUA_MAN = 2;
const int CHIEU_RONG_KHUNG_HINH = 48;
const int CHIEU_DAI_KHUNG_HINH = 36;
const int SO_KHUNG_HINH = 3;
const char* WINDOW_TITLE = "Flappy Bird";

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
TTF_Font* font=NULL;
TTF_Font* font1=NULL;
Mix_Music* music=NULL;
Mix_Music *music1=NULL;
Mix_Chunk* effect1=NULL;
Mix_Chunk *effect2=NULL;
Mix_Chunk *effect3=NULL;
SDL_Texture* backgroundTexture=NULL;
SDL_Texture *birdTexture=NULL;
SDL_Texture* birdTexture1=NULL;
SDL_Texture *pipeTexture=NULL;
SDL_Texture *backgroundTexture1=NULL;
SDL_Texture* soundimage=NULL;
SDL_Texture *muteimage=NULL;
SDL_Texture *bombTexture=NULL;
SDL_Texture* scoreTexture = NULL;
SDL_Texture *highestscoreTexture = NULL;

SDL_Color red = {255, 0, 0};
SDL_Color white = {255, 255, 255};

bool running = true;
bool gamestarted = false;
bool gameover = false;
int bgPosition = 0;
int frame = 0;
int score = 0;
int highestscore = 0;
int van_toc=0;
int gamemode=1;
int winner=0;
int van_toc1 = 0;
int van_toc2 = 0;

SDL_Rect bird1 = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
SDL_Rect bird2 = {50, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};


SDL_Rect bird;
SDL_Rect textrect = {280, 50, 450, 150};
SDL_Rect textrect1 = {375, 250,250, 120};
SDL_Rect textrect2 = {355, 400, 300, 120};
SDL_Rect textrect3 = {410, 550, 175, 75};
SDL_Rect textrect4 = {350, 50, 300, 100};
SDL_Rect textrect5 = {350, 325, 325, 100};
SDL_Rect textrect6 = {400, 500, 200, 75};
SDL_Rect textrect7 = {300,50,400,200};
SDL_Rect soundrect = {75, 75, 75, 75};
SDL_Rect scorerect = {675, 75, 50, 50};
SDL_Rect mode1 = {175, 250,250, 120};
SDL_Rect mode2 = {475, 250,250, 120};

SDL_Rect highestscorerect = {675,150,50,50};
SDL_Rect animation[SO_KHUNG_HINH];
SDL_Rect animation1[SO_KHUNG_HINH];

struct Pipe {
    int x, height;
    bool pass;
};

vector <Pipe> pipes;

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL();

SDL_Renderer* createRenderer();

void init ();

void quitSDL();

void renderTexture(SDL_Texture *texture, SDL_Rect rect);

void renderfullscreen(SDL_Texture* texture, int x, int y);

SDL_Texture* loadTexture(const char* filename);

void loadtext(const char* fontstyle, int size, const char* s);

void scrollingbackground(SDL_Texture* texture);

bool checkvacham(SDL_Rect a, SDL_Rect b);

void beforeGameStarted();

void countdown();

void ayready();

void reset(vector<Pipe>& pipes);

void reset1(vector<Pipe>& pipes);

void GameOver(vector<Pipe>& pipes);

void GameOver1(vector<Pipe>& pipes);

void GameOver2(vector<Pipe>& pipes);

void updateScoreTexture(const string& scoreText, SDL_Texture*& texture, SDL_Rect& rect);

void ingame(vector<Pipe>& pipes);

void playmode();

void destroy ();

int main(int argc, char* argv[]) {
    srand(time(0));
    init();
    SDL_Event event;

    while (running) {
        if (gamestarted == false) beforeGameStarted();
        else if(gamestarted==true && gameover==false && gamemode==1) {
            ingame(pipes);
        } else if (gamestarted==true&&gameover==false&&gamemode==2) {
            playmode();
        } else if (gamestarted==true && gameover==true&&gamemode==1) {
            GameOver(pipes);
        }
        else if (gameover==true && gamestarted==true&&gamemode==2&&winner==1) {
                GameOver1(pipes);
        } else if (gameover==true && gamestarted==true&&gamemode==2&&winner==2) {
        GameOver2(pipes);
        }
    }

    destroy();
    return 0;
}

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    return window;
}

SDL_Renderer* createRenderer() {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void init () {
    window = initSDL();
    renderer = createRenderer();
    TTF_Init();

    font = TTF_OpenFont("arial.ttf", 50);
    font1 = TTF_OpenFont("arial.ttf",32);

    Mix_OpenAudio (44100,MIX_DEFAULT_FORMAT,2,4096);
    music=Mix_LoadMUS("birds-isaiah658.ogg");
    music1=Mix_LoadMUS("Orbital Colossus.mp3");
    effect1=Mix_LoadWAV("flapping1.wav");
    effect2=Mix_LoadWAV("fb_collision_refined.wav");
    effect3=Mix_LoadWAV("ting_ting.wav");
    Mix_PlayMusic(music,-1);

    backgroundTexture = loadTexture("flappybackground.png");
    birdTexture = loadTexture("flapspritesheet2.png");
    birdTexture1=loadTexture("flappybirdnhon2.png");
    pipeTexture = loadTexture("pipe4.png");
    backgroundTexture1 = loadTexture("forest.jpg");
    soundimage = loadTexture( "sound1.png");
    muteimage = loadTexture("mute1.png");
    bombTexture = loadTexture ("bomb1.png");

    bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};

    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({SCREEN_WIDTH + i * 300, height, false});
    }

    for (int i = 0; i < SO_KHUNG_HINH; i++) {
        animation[i].x = i * CHIEU_RONG_KHUNG_HINH;
        animation[i].y = 0;
        animation[i].w = CHIEU_RONG_KHUNG_HINH;
        animation[i].h = CHIEU_DAI_KHUNG_HINH;
    }

    for (int i = 0; i < SO_KHUNG_HINH; i++) {
        animation1[i].x = i * CHIEU_RONG_KHUNG_HINH;
        animation1[i].y = 0;
        animation1[i].w = CHIEU_RONG_KHUNG_HINH;
        animation1[i].h = CHIEU_DAI_KHUNG_HINH;
    }

}

void quitSDL() {
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderTexture(SDL_Texture *texture, SDL_Rect rect)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void renderfullscreen(SDL_Texture* texture, int x, int y) {
    SDL_Rect dest = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture* loadTexture(const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void loadtext( const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect textrect) {
    TTF_Font* font = TTF_OpenFont(fontstyle, size);
    SDL_Surface* text = TTF_RenderText_Solid(font, s, color);
    SDL_Texture* texttf = SDL_CreateTextureFromSurface(renderer, text);
    SDL_RenderCopy(renderer, texttf, NULL, &textrect);

    SDL_DestroyTexture(texttf);
    TTF_CloseFont(font);
}

void scrollingbackground( SDL_Texture* texture) {
    bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
    if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;
    renderfullscreen(texture, bgPosition, 0);
    renderfullscreen(texture, bgPosition + SCREEN_WIDTH, 0);
}

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

void updateScoreTexture(const string& scoreText, SDL_Texture*& texture, SDL_Rect& rect) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font1, scoreText.c_str(), white);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}

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

void beforeGameStarted() {
    bool checksound = 1;

    while (gamestarted == false && running == true) {
        SDL_RenderClear(renderer);

        SDL_Rect firstbg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, backgroundTexture1, NULL, &firstbg);

        loadtext("UncialAntiqua-Regular.ttf",60,red,"Flappy Bird",textrect);
        loadtext("Arial.ttf", 40, red, "1 Player", mode1);
        loadtext("Arial.ttf", 40, red, "2 Player", mode2);
        loadtext("Arial.ttf", 40, red, "Instruction", textrect2);
        loadtext("Arial.ttf", 32, red, "Exit", textrect3);

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
                   // gamemode = 1;

                } else if (x >= mode2.x && x <= mode2.x + mode2.w && y >= mode2.y && y <= mode2.y + mode2.h) {
                    gamemode = 2;
                    countdown();
                    gamestarted = true;
                    //gamemode = 2;
                }
                else if (x >= soundrect.x && x <= soundrect.x + soundrect.w && y >= soundrect.y && y <= soundrect.y + soundrect.h) {
                    if (Mix_PlayingMusic()==0 && checksound==0) {
                        Mix_PlayMusic(music1,-1);
                        checksound=1;
                    } else if (Mix_PlayingMusic()==1 && checksound==1){
                         Mix_HaltMusic();
                        checksound=0;
                    }

                }
                else if (x >= textrect3.x && x <= textrect3.x + textrect3.w && y >= textrect3.y && y <= textrect3.y + textrect3.h) {
                    running = false;
                }
            }
        }
    }
}


void reset(vector<Pipe>& pipes) {
    gamestarted = true;
    gameover = false;
    bird.y = SCREEN_HEIGHT / 2;
    van_toc = 0;
    TOC_DO_DICH_CHUYEN_CUA_ONG=5;

    pipes.clear();
    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({ SCREEN_WIDTH + i * 300, height });
    }
}

void reset1(vector<Pipe>& pipes) {
    gamestarted = true;
    gameover =false;
    winner=0;
    bird1.y = SCREEN_HEIGHT / 2;
    bird2.y = SCREEN_HEIGHT/2;
    van_toc1 = 0;
    van_toc2 = 0;
    TOC_DO_DICH_CHUYEN_CUA_ONG=5;

    pipes.clear();
    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({ SCREEN_WIDTH + i * 300, height });
    }
}

void GameOver(vector<Pipe>& pipes) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("UncialAntiqua-Regular.ttf",60,red,"Game Over",textrect7);
    loadtext("Arial.ttf", 32, red, "Play again", textrect5);
    loadtext("Arial.ttf", 32, red, "Exit", textrect6);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect5.x && x <= textrect5.x + textrect5.w && y >= textrect5.y && y <= textrect5.y + textrect5.h) {
                ayready();
                reset(pipes);
                return;
            }
            else if (x >= textrect6.x && x <= textrect6.x + textrect6.w && y >= textrect6.y && y <= textrect6.y + textrect6.h) {
                running = false;
                return;
            }
        }
    }
}

void GameOver1(vector<Pipe>& pipes) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("UncialAntiqua-Regular.ttf",60,red,"player1win",textrect7);
    loadtext("Arial.ttf", 32, red, "Play again", textrect5);
    loadtext("Arial.ttf", 32, red, "Exit", textrect6);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect5.x && x <= textrect5.x + textrect5.w && y >= textrect5.y && y <= textrect5.y + textrect5.h) {
                ayready();
                reset1(pipes);
                return;
            }
            else if (x >= textrect6.x && x <= textrect6.x + textrect6.w && y >= textrect6.y && y <= textrect6.y + textrect6.h) {
                running = false;
                return;
            }
        }
    }
}

void GameOver2(vector<Pipe>& pipes) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture1, NULL, &bgRect1);

    loadtext("UncialAntiqua-Regular.ttf",60,red,"player2win",textrect7);
    loadtext("Arial.ttf", 32, red, "Play again", textrect5);
    loadtext("Arial.ttf", 32, red, "Exit", textrect6);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect5.x && x <= textrect5.x + textrect5.w && y >= textrect5.y && y <= textrect5.y + textrect5.h) {
                ayready();
                reset1(pipes);
                return;
            }
            else if (x >= textrect6.x && x <= textrect6.x + textrect6.w && y >= textrect6.y && y <= textrect6.y + textrect6.h) {
                running = false;
                return;
            }
        }
    }
}


void ingame(vector<Pipe>& pipes) {
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
            score = 0;
        }
    }

    if (bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) {
        Mix_PlayChannel(-1, effect2, 0);
        gameover = true;
        score = 0;
    }

    SDL_RenderClear(renderer);
    scrollingbackground(backgroundTexture);

    string scoreText = "Score: " + to_string(score);
    string highestscoreText = "Highest score: " + to_string(highestscore);

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

void destroy () {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyTexture(backgroundTexture1);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(soundimage);
    SDL_DestroyTexture(muteimage);
    SDL_DestroyTexture (highestscoreTexture);

    TTF_CloseFont(font);
    TTF_CloseFont(font1);

    Mix_FreeMusic(music);
    Mix_FreeMusic(music1);

    Mix_FreeChunk(effect1);
    Mix_FreeChunk(effect2);
    Mix_FreeChunk(effect3);

    quitSDL();
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

    SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird1);
    SDL_RenderCopy(renderer, birdTexture1, &animation1[frame], &bird2);

    for (int i = 0; i < pipes.size(); i++) {
        SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
        SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

        SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
        SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(8);

    frame = (frame + 1) % SO_KHUNG_HINH;
}
