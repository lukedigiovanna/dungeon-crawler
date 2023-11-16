#pragma once

#include <string>
#include <SDL.h>

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Window(std::string name);
    ~Window();
};