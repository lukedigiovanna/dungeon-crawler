#include "Window.h"

#include <iostream>

Window::Window(std::string name) {
    scWidth = 640;
    scHeight = 480;
    window = SDL_CreateWindow(name.c_str(), 120, 120, scWidth, scHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_AddEventWatch(Window::resizeEventWatcher, this);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::updateWindowSize() {
    SDL_GetWindowSize(window, &scWidth, &scHeight);
}

int Window::resizeEventWatcher(void* data, SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        Window* window = static_cast<Window*>(data);
        window->updateWindowSize();
    }

    return 0;
}