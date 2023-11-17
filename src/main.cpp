#include <SDL.h>
#include <iostream>

#include "engine/utils/Math.h"
#include "engine/graphics/Window.h"
#include "engine/Engine.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Engine engine("Cool");
    engine.run();

    return 0;

    // // Initialize SDL
    // if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    //     std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    //     return 1;
    // }

    // // Create a window
    // SDL_Window *window = SDL_CreateWindow("SDL2 Rectangle", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    // if (window == nullptr) {
    //     std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // // Create a renderer
    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if (renderer == nullptr) {
    //     SDL_DestroyWindow(window);
    //     std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     return 1;
    // }

    // // Main loop
    

    //     // Update screen
    //     SDL_RenderPresent(renderer);
    // }

    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}
