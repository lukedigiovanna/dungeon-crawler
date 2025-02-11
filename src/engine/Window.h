#pragma once

#include <string>
#include <SDL.h>

class Window {
public:
    static float DEFAULT_WIDTH;
    static float DEFAULT_HEIGHT;
private:
    float scWidth, scHeight;
    static int resizeEventWatcher(void* data, SDL_Event* event);
public:
    SDL_Window* window;
    SDL_GLContext gl;
    Window(std::string name);
    ~Window();

    void updateWindowSize();

    inline float width() const {
        return scWidth;
    }
    inline float height() const {
        return scHeight;
    }
};