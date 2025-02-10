#pragma once

#include <string>
#include <SDL.h>

class Window {
public:
    static int DEFAULT_WINDOW_WIDTH;
    static int DEFAULT_WINDOW_HEIGHT;
private:
    int scWidth, scHeight;
    static int resizeEventWatcher(void* data, SDL_Event* event);
public:
    SDL_Window* window;
    SDL_GLContext gl;
    Window(std::string name);
    ~Window();

    void updateWindowSize();

    inline int width() const {
        return scWidth;
    }
    inline int height() const {
        return scHeight;
    }
};