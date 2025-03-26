#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
const int TOC_DO_DICH_CHUYEN_CUA_ONG = 5;
const int TOC_DO_DICH_CHUYEN_CUA_MAN = 2;
const int CHIEU_RONG_KHUNG_HINH= 48;
const int CHIEU_DAI_KHUNG_HINH=36;
const int SO_KHUNG_HINH=3;
const char* WINDOW_TITLE = "Flappy Bird";

struct Pipe {
    int x, height;
};

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);

SDL_Renderer* createRenderer(SDL_Window* window);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer);

void renderfullscreen (SDL_Texture* texture,int x,int y,SDL_Renderer* renderer);

SDL_Texture *loadTexture(SDL_Renderer* renderer,const char *filename);

void loadtext(SDL_Renderer* renderer,const char* fontstyle,int size,SDL_Color color,const char* s,SDL_Rect textrect);

void scrollingbackground (SDL_Renderer* renderer,SDL_Texture* texture,int &bgPosition);

bool checkvacham(SDL_Rect a, SDL_Rect b);

void reset(bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, std::vector<Pipe>& pipes);

void beforeGameStarted (SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color red, SDL_Rect textrect,SDL_Rect textrect1,SDL_Rect textrect2,SDL_Rect textrect3,bool &running,bool &gamestarted);
    
void GameOver(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect textrect4, SDL_Rect textrect5, SDL_Rect textrect6, bool& running, bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, vector<Pipe>& pipes,SDL_Color red);


int main(int argc, char* argv[]) {
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    TTF_Init();

    SDL_Texture* backgroundTexture = loadTexture(renderer, "flappybackground.png");
    SDL_Texture* birdTexture = loadTexture(renderer, "flapspritesheet2.png");
    SDL_Texture* pipeTexture = loadTexture(renderer, "pipe4.png");
    SDL_Texture* backgroundTexture1=loadTexture(renderer, "forest.jpg");

    if (!backgroundTexture || !birdTexture || !pipeTexture || !backgroundTexture1) {
        return -1;
    }

    SDL_Color red = {255,0,0};

    SDL_Rect textrect={350,50,320,120};
    SDL_Rect textrect1={400,250,200,120};
    SDL_Rect textrect2={365,400,300,120};
    SDL_Rect textrect3={400,550,200,75};
    SDL_Rect textrect4= {350,50,300,100};
    SDL_Rect textrect5 = {380,275,200,100};
    SDL_Rect textrect6={380,425,200,50};

    SDL_Rect bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};
    
    int van_toc = 0;
    int bgPosition=0;
    int frame=0;

    bool delay=true;
    bool running = true;
    bool gamestarted = false;
    bool gameover = false;

    SDL_Event event;

    vector <Pipe> pipes;

    srand(time(0));

    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({SCREEN_WIDTH + i * 300, height});
    }

    SDL_Rect animation[SO_KHUNG_HINH];

    for (int i=0;i<SO_KHUNG_HINH;i++) {
        animation[i].x=i*CHIEU_RONG_KHUNG_HINH;
        animation[i].y=0;
        animation[i].w=CHIEU_RONG_KHUNG_HINH;
        animation[i].h=CHIEU_DAI_KHUNG_HINH;
    }

    while (running) {
        if (gamestarted ==false) beforeGameStarted(renderer,backgroundTexture1,red,textrect,textrect1,textrect2,textrect3,running,gamestarted);
        else {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) ||(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT))  {
                if (gamestarted==false) {
                    gamestarted = true;
                }
                van_toc = LUC_NHAY;
            }
        }

        if (gamestarted) {
            van_toc += TRONGLUC;
            bird.y += van_toc;

            for (int i=0;i<3;i++) {
                pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG;
                if (pipes[i].x + CHIEU_RONG_ONG < 0) {
                    pipes[i].x = SCREEN_WIDTH;
                    pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
                }

                SDL_Rect Ong_tren={pipes[i].x,0,CHIEU_RONG_ONG,pipes[i].height};
                SDL_Rect Ong_duoi={pipes[i].x,pipes[i].height+KHOANG_CACH_GIUA_HAI_ONG,CHIEU_RONG_ONG,SCREEN_HEIGHT-pipes[i].height-KHOANG_CACH_GIUA_HAI_ONG};
                if (checkvacham(bird,Ong_tren)||checkvacham(bird,Ong_duoi)) gameover = true;
            }
            if (bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) gameover = true;
        }
        if (gameover) {
            GameOver(renderer, backgroundTexture, textrect4, textrect5, textrect6, running, gamestarted, gameover, bird, van_toc, pipes,red);
        } else {
        SDL_RenderClear(renderer);
        scrollingbackground(renderer,backgroundTexture,bgPosition);

        SDL_RenderCopy (renderer,birdTexture,&animation[frame],&bird);

        for (int i=0;i<3;i++) {
            SDL_Rect Ong_tren = {pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height};
            SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

            SDL_Rect Ong_duoi = {pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG};
            SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        frame=(frame+1)%SO_KHUNG_HINH;
        if (frame >= SO_KHUNG_HINH) frame=0;
    }
    }
}
    SDL_DestroyTexture (backgroundTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyTexture(backgroundTexture1);
    quitSDL(window,renderer);
    return 0;
}

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void renderfullscreen (SDL_Texture* texture,int x,int y,SDL_Renderer* renderer) {
    SDL_Rect dest={x,y,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderCopy(renderer,texture,NULL,&dest);
}

SDL_Texture *loadTexture(SDL_Renderer* renderer,const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}
void loadtext(SDL_Renderer* renderer,const char* fontstyle,int size,SDL_Color color,const char* s,SDL_Rect textrect) {
    TTF_Font* font = TTF_OpenFont (fontstyle,size);
    SDL_Surface* text = TTF_RenderText_Solid (font,s,color);
    SDL_Texture* texttf = SDL_CreateTextureFromSurface(renderer,text);
    SDL_RenderCopy(renderer,texttf,NULL,&textrect);

    SDL_DestroyTexture(texttf); 
    TTF_CloseFont(font); 
}

void scrollingbackground (SDL_Renderer* renderer,SDL_Texture* texture,int &bgPosition) {
    bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
    if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;
    renderfullscreen(texture,bgPosition,0,renderer);
    renderfullscreen(texture,bgPosition+SCREEN_WIDTH,0,renderer);
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

void reset(bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, std::vector<Pipe>& pipes) {
    gameStarted = true;
    gameover = false;
    bird.y = SCREEN_HEIGHT / 2;
    van_toc = 0;

    pipes.clear();
    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({SCREEN_WIDTH + i * 300, height});
    }
}

void beforeGameStarted (SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color red, SDL_Rect textrect,SDL_Rect textrect1,SDL_Rect textrect2,SDL_Rect textrect3,bool &running,bool &gamestarted) {
    SDL_Rect firstbg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &firstbg);

    loadtext(renderer,"Antumn Wonderful.ttf",60,red,"Flappy Bird",textrect);
    loadtext (renderer,"8bitOperatorPlus8-Regular.ttf",32,red,"Start",textrect1);
    loadtext (renderer,"8bitOperatorPlus8-Regular.ttf",32,red,"Instruction",textrect2);
    loadtext (renderer,"8bitOperatorPlus8-Regular.ttf",32,red,"Exit",textrect3);

    SDL_RenderPresent(renderer);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect1.x && x <= textrect1.x + textrect1.w && y >= textrect1.y && y <= textrect1.y + textrect1.h) {
                gamestarted = true;
            }
            if (x >= textrect3.x && x <= textrect3.x + textrect3.w && y >= textrect3.y && y <= textrect3.y + textrect3.h) {
                    running = false;
                }
            }
        }
}

void GameOver(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect textrect4, SDL_Rect textrect5, SDL_Rect textrect6, bool& running, bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, vector<Pipe>& pipes,SDL_Color red) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);

    loadtext(renderer,"Antumn Wonderful.ttf",60,red,"Game Over",textrect4);
    loadtext (renderer,"8bitOperatorPlus8-Regular.ttf",32,red,"Start again",textrect5);
    loadtext (renderer,"8bitOperatorPlus8-Regular.ttf",32,red,"Exit",textrect6);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect5.x && x <= textrect5.x + textrect5.w && y >= textrect5.y && y <= textrect5.y + textrect5.h) {
                reset(gameStarted, gameover, bird, van_toc, pipes);
                return;
            } else if (x >= textrect6.x && x <= textrect6.x + textrect6.w && y >= textrect6.y && y <= textrect6.y + textrect6.h) {
                running = false;
                return;
            }
        }
    }
}



