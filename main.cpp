#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
const int TOC_DO_DICH_CHUYEN_CUA_ONG = 5;
const int TOC_DO_DICH_CHUYEN_CUA_MAN = 2;
const int CHIEU_RONG_KHUNG_HINH = 48;
const int CHIEU_DAI_KHUNG_HINH = 36;
const int SO_KHUNG_HINH = 3;
const char* WINDOW_TITLE = "Flappy Bird";

struct Pipe {
    int x, height;
    bool pass;
};

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);

SDL_Renderer* createRenderer(SDL_Window* window);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void renderTexture(SDL_Texture *texture, SDL_Rect rect, SDL_Renderer* renderer);

void renderfullscreen(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename);

void loadtext(SDL_Renderer* renderer, const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect textrect); 

void scrollingbackground(SDL_Renderer* renderer, SDL_Texture* texture, int& bgPosition);

bool checkvacham(SDL_Rect a, SDL_Rect b);

void beforeGameStarted(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture* texture2, SDL_Texture* texture3, SDL_Color red,SDL_Color white, SDL_Rect textrect, SDL_Rect textrect1, SDL_Rect textrect2, SDL_Rect textrect3, SDL_Rect soundrect, bool& running, bool& gamestarted);

void reset(bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, std::vector<Pipe>& pipes);

void GameOver(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect textrect7, SDL_Rect textrect5, SDL_Rect textrect6, bool& running, bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, vector<Pipe>& pipes, SDL_Color red);

void updateScoreTexture(SDL_Renderer* renderer, const string& scoreText, TTF_Font* font, SDL_Color color, SDL_Texture*& texture, SDL_Rect& rect);


int main(int argc, char* argv[]) {
    SDL_Window* window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer = createRenderer(window);
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("arial.ttf", 32);
    if (font == nullptr) {
        cerr << "TTF_OpenFont error: " << TTF_GetError() << endl;
        return -1;
    }

    SDL_Texture* backgroundTexture = loadTexture(renderer, "flappybackground.png");
    SDL_Texture* birdTexture = loadTexture(renderer, "flapspritesheet2.png");
    SDL_Texture* pipeTexture = loadTexture(renderer, "pipe4.png");
    SDL_Texture* backgroundTexture1 = loadTexture(renderer, "forest.jpg");
    SDL_Texture* soundimage = loadTexture(renderer, "sound1.png");
    SDL_Texture* muteimage = loadTexture(renderer, "mute1.png");
    SDL_Texture* scoreTexture = NULL;
    SDL_Texture* highestscoreTexture = NULL;

    if (!backgroundTexture || !birdTexture || !pipeTexture || !backgroundTexture1 || !soundimage) {
        return -1;
    }

    SDL_Color red = {255, 0, 0};
    SDL_Color white = {255, 255, 255};

    SDL_Rect textrect = {280, 50, 450, 150};
    SDL_Rect textrect1 = {375, 250,250, 120};
    SDL_Rect textrect2 = {355, 400, 300, 120};
    SDL_Rect textrect3 = {400, 550, 175, 75};
    SDL_Rect textrect4 = {350, 50, 300, 100};
    SDL_Rect textrect5 = {340, 325, 325, 100};
    SDL_Rect textrect6 = {350, 500, 250, 100};
    SDL_Rect textrect7 = {300,50,400,200};

    SDL_Rect soundrect = {75, 75, 75, 75};
    SDL_Rect scorerect = {675, 75, 50, 50};
    SDL_Rect highestscorerect = {675,150,50,50};

    SDL_Rect bird = {100, SCREEN_HEIGHT / 2, CHIEU_RONG_KHUNG_HINH, CHIEU_DAI_KHUNG_HINH};

    int van_toc = 0;
    int bgPosition = 0;
    int frame = 0;
    int score = 0;
    int highestscore = 0;

    bool running = true;
    bool gamestarted = false;
    bool gameover = false;

    SDL_Event event;

    vector <Pipe> pipes;

    srand(time(0));

    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({SCREEN_WIDTH + i * 300, height, false}); 
    }

    SDL_Rect animation[SO_KHUNG_HINH];

    for (int i = 0; i < SO_KHUNG_HINH; i++) {
        animation[i].x = i * CHIEU_RONG_KHUNG_HINH;
        animation[i].y = 0;
        animation[i].w = CHIEU_RONG_KHUNG_HINH;
        animation[i].h = CHIEU_DAI_KHUNG_HINH;
    }

    while (running) {
        if (gamestarted == false) beforeGameStarted(renderer, backgroundTexture1, soundimage, muteimage, red,white, textrect, textrect1, textrect2, textrect3, soundrect, running, gamestarted);
        else {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) || (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) {
                    if (gamestarted == false) {
                        gamestarted = true;
                    }
                    van_toc = LUC_NHAY;
                }
            }

            if (gamestarted) {
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
                        pipes[i].pass = true;
                        if (score > highestscore) {
                            highestscore ++;
                        }
                    }

                    SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
                    SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
                    if (checkvacham(bird, Ong_tren) || checkvacham(bird, Ong_duoi)) {
                        gameover = true;
                        score = 0;
                    }
                }
                if (bird.y + bird.h > SCREEN_HEIGHT || bird.y < 0) {
                    gameover = true;
                    score = 0;
                }
            }
            if (gameover) {
                GameOver(renderer, backgroundTexture1, textrect7, textrect5, textrect6, running, gamestarted, gameover, bird, van_toc, pipes, red);
            }
            else {
                SDL_RenderClear(renderer);
                scrollingbackground(renderer, backgroundTexture, bgPosition);

                string scoreText = "Score: " + to_string(score);
                string highestscoreText = "Highest score: " + to_string(highestscore);
                
              
                updateScoreTexture(renderer, scoreText, font, white, scoreTexture, scorerect);
                updateScoreTexture(renderer, highestscoreText, font, white, highestscoreTexture, highestscorerect);
              

                SDL_RenderCopy(renderer, birdTexture, &animation[frame], &bird);

                for (int i = 0; i < pipes.size(); i++) {
                    SDL_Rect Ong_tren = { pipes[i].x, 0, CHIEU_RONG_ONG, pipes[i].height };
                    SDL_RenderCopy(renderer, pipeTexture, NULL, &Ong_tren);

                    SDL_Rect Ong_duoi = { pipes[i].x, pipes[i].height + KHOANG_CACH_GIUA_HAI_ONG, CHIEU_RONG_ONG, SCREEN_HEIGHT - pipes[i].height - KHOANG_CACH_GIUA_HAI_ONG };
                    SDL_RenderCopyEx(renderer, pipeTexture, NULL, &Ong_duoi, 0, NULL, SDL_FLIP_VERTICAL);
                }
              
                if (scoreTexture != NULL) {
                    SDL_RenderCopy(renderer, scoreTexture, NULL, &scorerect);
                }

                if (highestscoreTexture != NULL) {
                    SDL_RenderCopy(renderer, highestscoreTexture, NULL, &highestscorerect);
                }

                SDL_RenderPresent(renderer);
                SDL_Delay(8);
                frame = (frame + 1) % SO_KHUNG_HINH;
                if (frame >= SO_KHUNG_HINH) frame = 0;
            }
        }
    }

   
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(pipeTexture);
    SDL_DestroyTexture(backgroundTexture1);
    SDL_DestroyTexture(scoreTexture); 
    TTF_CloseFont(font);           
    quitSDL(window, renderer);
    return 0;
}

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer) {
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderTexture(SDL_Texture *texture, SDL_Rect rect, SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void renderfullscreen(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer) {
    SDL_Rect dest = { x, y, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void loadtext(SDL_Renderer* renderer, const char* fontstyle, int size, SDL_Color color, const char* s, SDL_Rect textrect) { // Hàm loadtext cũ
    TTF_Font* font = TTF_OpenFont(fontstyle, size);
    SDL_Surface* text = TTF_RenderText_Solid(font, s, color);
    SDL_Texture* texttf = SDL_CreateTextureFromSurface(renderer, text);
    SDL_RenderCopy(renderer, texttf, NULL, &textrect);

    SDL_DestroyTexture(texttf);
    TTF_CloseFont(font);
}

void scrollingbackground(SDL_Renderer* renderer, SDL_Texture* texture, int& bgPosition) {
    bgPosition -= TOC_DO_DICH_CHUYEN_CUA_MAN;
    if (bgPosition <= -SCREEN_WIDTH) bgPosition = 0;
    renderfullscreen(texture, bgPosition, 0, renderer);
    renderfullscreen(texture, bgPosition + SCREEN_WIDTH, 0, renderer);
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

void beforeGameStarted(SDL_Renderer* renderer, SDL_Texture* texture1, SDL_Texture* texture2, SDL_Texture* texture3, SDL_Color red,SDL_Color white, SDL_Rect textrect, SDL_Rect textrect1, SDL_Rect textrect2, SDL_Rect textrect3, SDL_Rect soundrect, bool& running, bool& gamestarted) {
    bool checksound = 1;

    while (gamestarted == false && running == true) {
        SDL_RenderClear(renderer);

        SDL_Rect firstbg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
        SDL_RenderCopy(renderer, texture1, NULL, &firstbg);

        loadtext(renderer,"UncialAntiqua-Regular.ttf",60,red,"Flappy Bird",textrect);
        loadtext(renderer, "Arial.ttf", 40, red, "Play Game", textrect1);
        loadtext(renderer, "Arial.ttf", 40, red, "Instruction", textrect2);
        loadtext(renderer, "Arial.ttf", 32, red, "Exit", textrect3);

        if (checksound == 1) {
            renderTexture(texture2, soundrect, renderer);
        }
        else if (checksound == 0) {
            renderTexture(texture3, soundrect, renderer);
        }

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
                else if (x >= soundrect.x && x <= soundrect.x + soundrect.w && y >= soundrect.y && y <= soundrect.y + soundrect.h) {
                    if (checksound == 1) checksound = 0;
                    else if (checksound == 0) checksound = 1;
                }
                else if (x >= textrect3.x && x <= textrect3.x + textrect3.w && y >= textrect3.y && y <= textrect3.y + textrect3.h) {
                    running = false;
                }
            }
        }
    }
}

void reset(bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, std::vector<Pipe>& pipes) {
    gameStarted = true;
    gameover = false;
    bird.y = SCREEN_HEIGHT / 2;
    van_toc = 0;

    pipes.clear();
    for (int i = 0; i < 3; i++) {
        int height = rand() % (SCREEN_HEIGHT - KHOANG_CACH_GIUA_HAI_ONG - 100) + 50;
        pipes.push_back({ SCREEN_WIDTH + i * 300, height });
    }
}

void GameOver(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect textrect7, SDL_Rect textrect5, SDL_Rect textrect6, bool& running, bool& gameStarted, bool& gameover, SDL_Rect& bird, int& van_toc, vector<Pipe>& pipes, SDL_Color red) {
    SDL_RenderClear(renderer);
    SDL_Rect bgRect1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);

    loadtext(renderer,"UncialAntiqua-Regular.ttf",60,red,"Game Over",textrect7);
    loadtext(renderer, "ArialMdm.ttf", 32, red, "Play again", textrect5);
    loadtext(renderer, "ArialMdm.ttf", 32, red, "Exit", textrect6);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x, y = event.button.y;
            if (x >= textrect5.x && x <= textrect5.x + textrect5.w && y >= textrect5.y && y <= textrect5.y + textrect5.h) {
                reset(gameStarted, gameover, bird, van_toc, pipes);
                return;
            }
            else if (x >= textrect6.x && x <= textrect6.x + textrect6.w && y >= textrect6.y && y <= textrect6.y + textrect6.h) {
                running = false;
                return;
            }
        }
    }
}

void updateScoreTexture(SDL_Renderer* renderer, const string& scoreText, TTF_Font* font, SDL_Color color, SDL_Texture*& texture, SDL_Rect& rect) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    rect.w = textSurface->w;
    rect.h = textSurface->h;
    SDL_FreeSurface(textSurface);
}


