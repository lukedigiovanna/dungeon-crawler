#pragma once

#include <string>
#include <SDL.h>

class Window {
private:
    SDL_Window* window;
public:
    SDL_Renderer* renderer;
    Window(std::string name);
    ~Window();
};