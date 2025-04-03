#include "declare.h"
#include "Init.h"
#include "graphic.h"

// Hàm kiểm tra,báo lỗi và thoát chương trình
void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

// Khởi tạo SDL và tạo cửa sổ
SDL_Window* initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    return window;
}

// Khởi tạo renderer
SDL_Renderer* createRenderer() {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

// Khởi tạo các thành phần của game
void init () {
    window = initSDL();
    renderer = createRenderer();
    TTF_Init();

    // Tải font chữ
    font = TTF_OpenFont("font/arial.ttf", 50);
    font1 = TTF_OpenFont("font/arial.ttf",32);

    // Tải âm thanh
    Mix_OpenAudio (44100,MIX_DEFAULT_FORMAT,2,4096);
    music=Mix_LoadMUS("sound/birds-isaiah658.ogg");
    soundflap=Mix_LoadWAV("sound/flapping4.wav");
    soundvacham=Mix_LoadWAV("sound/fb_collision_refined1.wav");
    soundting_ting=Mix_LoadWAV("sound/ting_ting.wav");
    explode=Mix_LoadWAV("sound/explosion.wav");
    Mix_PlayMusic(music,-1);

    // Tải hình ảnh
    backgroundTexture = loadTexture("image/flappybackground.png");
    birdTexture = loadTexture("image/flapspritesheet2.png");
    birdTexture1=loadTexture("image/orangebird1.png");
    birdTexture2=loadTexture("image/redbird1.png");
    pipeTexture = loadTexture("image/pipe4.png");
    bombTexture = loadTexture("image/bomb1.png");
    healthTexture = loadTexture("image/bohuyet.png");
    rankimage = loadTexture("image/ranking.png");
    backgroundTexture1 = loadTexture("image/FLAPPYBIRD.png");
    backgroundTexture2 = loadTexture("image/night.jpg");
    soundimage = loadTexture( "image/unmute.png");
    muteimage = loadTexture("image/mute.png");
    homeimage = loadTexture("image/home.png");
    returnimage = loadTexture("image/return.png");
    heart1 = loadTexture("image/1heart.png");
    heart2 = loadTexture("image/2heart.png");
    heart3 = loadTexture("image/3heart.png");

    // Khởi tạo ống,bomb và health
    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({SCREEN_WIDTH + i * 400, height, false});
    }

    for (int i = 0; i < 3; i++) {
        int x = (SCREEN_WIDTH - 200) + i * 400 - CHIEU_RONG_BOM / 2; 
        int cachong = 15;
        int heightRef = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50; 
        int minY = heightRef + cachong;
        int maxY = minY + KHOANG_CACH_GIUA_HAI_ONG - CHIEU_DAI_BOM - 2 * cachong;
        int y = minY + rand() % (maxY - minY);
        bombs.push_back({x, y});
        
    }

    healths.push_back({SCREEN_WIDTH + 700, rand() % (500) + 100, false});
    healths.push_back({SCREEN_WIDTH + 3800, rand() % (500) + 100, false});

    for (int i = 0; i < SO_KHUNG_HINH; i++) {
        animation[i].x = i * CHIEU_RONG_KHUNG_HINH;
        animation[i].y = 0;
        animation[i].w = CHIEU_RONG_KHUNG_HINH;
        animation[i].h = CHIEU_DAI_KHUNG_HINH;
    }

}

void quitSDL() {
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


