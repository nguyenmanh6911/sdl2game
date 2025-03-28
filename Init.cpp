#include "declare.h"
#include "Init.h"
#include "graphic.h"

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
    effect1=Mix_LoadWAV("flapping1.wav");
    effect2=Mix_LoadWAV("fb_collision_refined.wav");
    effect3=Mix_LoadWAV("ting_ting.wav");
    Mix_PlayMusic(music,-1);

    backgroundTexture = loadTexture("flappybackground.png");
    birdTexture = loadTexture("flapspritesheet2.png");
    birdTexture1=loadTexture("orangebird1.png");
    birdTexture2=loadTexture("redbird1.png");
    pipeTexture = loadTexture("pipe4.png");
    backgroundTexture1 = loadTexture("forest.jpg");
    soundimage = loadTexture( "sound1.png");
    muteimage = loadTexture("mute1.png");

    // bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};

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

    for (int i = 0; i < SO_KHUNG_HINH1; i++) {
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


