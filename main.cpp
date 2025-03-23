#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cstdlib>
#include <ctime>
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

struct Pipe {
    int x, height;
};

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

int main(int argc, char* argv[]) {
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);

    SDL_Texture* backgroundTexture = loadTexture(renderer, "flappybackground.png");
    SDL_Texture* birdTexture = loadTexture(renderer, "flapspritesheet2.png");
    SDL_Texture* pipeTexture = loadTexture(renderer, "pipe4.png");

    if (!backgroundTexture || !birdTexture || !pipeTexture) {
        return -1;
    }

    SDL_Rect bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};

    int van_toc = 0;
    int bgPosition=0;
    int frame=0;
    bool running = true;
    bool gamestarted = false;

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
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                if (gamestarted==false) {
                    gamestarted = true;
                }
                van_toc = LUC_NHAY;
            }
        }

        if (gamestarted) {
            van_toc += TRONGLUC;
            bird.y += van_toc;

            bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
            if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;

            for (int i=0;i<3;i++) {
                pipes[i].x -= TOC_DO_DICH_CHUYEN_CUA_ONG;
                if (pipes[i].x + CHIEU_RONG_ONG < 0) {
                    pipes[i].x = SCREEN_WIDTH;
                    pipes[i].height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
                }

                SDL_Rect Ong_tren={pipes[i].x,0,CHIEU_RONG_ONG,pipes[i].height};
                SDL_Rect Ong_duoi={pipes[i].x,pipes[i].height+KHOANG_CACH_GIUA_HAI_ONG,CHIEU_RONG_ONG,SCREEN_HEIGHT-pipes[i].height-KHOANG_CACH_GIUA_HAI_ONG};
                if (checkvacham(bird,Ong_tren)||checkvacham(bird,Ong_duoi)) running = false;
            }
            if (bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) running = false;
        }
        SDL_RenderClear(renderer);

        renderfullscreen(backgroundTexture,bgPosition,0,renderer);
        renderfullscreen(backgroundTexture,bgPosition+SCREEN_WIDTH,0,renderer);

        
        SDL_RenderCopy (renderer,birdTexture,&animation[frame],&bird);

        for (int i=0;i<3;i++) {
            SDL_Rect Ong_tren = {pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height};
            SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

            SDL_Rect Ong_duoi = {pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG};
            SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        frame++;
        frame=(frame+1)%SO_KHUNG_HINH;
        if (frame >= SO_KHUNG_HINH) frame=0;
    }
    SDL_DestroyTexture (backgroundTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    quitSDL(window,renderer);
    return 0;
}










