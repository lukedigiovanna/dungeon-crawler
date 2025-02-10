#include "Window.h"

#include <iostream>

#include <glad/glad.h>

int Window::DEFAULT_WINDOW_WIDTH = 640;
int Window::DEFAULT_WINDOW_HEIGHT = 480;

Window::Window(std::string name) {
    scWidth = DEFAULT_WINDOW_WIDTH;
    scHeight = DEFAULT_WINDOW_HEIGHT;
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scWidth, scHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    gl = SDL_GL_CreateContext(window);
    SDL_AddEventWatch(Window::resizeEventWatcher, this);
}

Window::~Window() {
    SDL_GL_DeleteContext(this->gl);
    SDL_DestroyWindow(this->window);
}

void Window::updateWindowSize() {
    SDL_GetWindowSize(window, &scWidth, &scHeight);
    glViewport(0, 0, scWidth, scHeight);
}

int Window::resizeEventWatcher(void* data, SDL_Event* event) {
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        Window* window = static_cast<Window*>(data);
        window->updateWindowSize();
    }

    return 0;
}