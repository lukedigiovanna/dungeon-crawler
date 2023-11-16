#include "Window.h"

#include <iostream>

Window::Window(std::string name) {
    window = SDL_CreateWindow(name.c_str(), 120, 120, 680, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Window::~Window() {
    SDL_DestroyWindow(this->window);
}