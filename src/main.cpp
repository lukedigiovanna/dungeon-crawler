#include <SDL.h>
#include <iostream>

#include "engine/Engine.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Engine engine("Cool");
    engine.run();

    SDL_Quit();

    return 0;
}
