#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Lỗi khi khởi tạo SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Khởi tạo SDL2_image (hỗ trợ định dạng JPG, PNG, v.v.)
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        std::cerr << "Lỗi khi khởi tạo SDL2_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("Hiển thị ảnh JPG",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Lỗi khi tạo cửa sổ: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // Tạo renderer để vẽ
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Lỗi khi tạo renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // Tải ảnh từ file image.jpg
    SDL_Surface* imageSurface = IMG_Load("image.jpg");
    if (!imageSurface) {
        std::cerr << "Lỗi khi tải ảnh: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // Chuyển ảnh thành texture để hiển thị
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Giải phóng surface sau khi đã có texture

    if (!texture) {
        std::cerr << "Lỗi khi tạo texture: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        // Xử lý sự kiện (thoát khi nhấn dấu X)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Xóa màn hình và vẽ ảnh
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Giải phóng tài nguyên
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
