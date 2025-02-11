#include "Window.h"

#include <iostream>

#include <glad/glad.h>

float Window::DEFAULT_WIDTH = 640.0f;
float Window::DEFAULT_HEIGHT = 480.0f;

Window::Window(std::string name) {
    scWidth = DEFAULT_WIDTH;
    scHeight = DEFAULT_HEIGHT;
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    gl = SDL_GL_CreateContext(window);
    SDL_AddEventWatch(Window::resizeEventWatcher, this);
}

Window::~Window() {
    SDL_GL_DeleteContext(this->gl);
    SDL_DestroyWindow(this->window);
}

void Window::updateWindowSize() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    scWidth = w;
    scHeight = h;
}

int Window::resizeEventWatcher(void* data, SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        Window* window = static_cast<Window*>(data);
        window->updateWindowSize();
    }

    return 0;
}