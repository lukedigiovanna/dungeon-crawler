#pragma once

#include <string>
#include <SDL.h>

class Window {
private:
    SDL_Window* window;
    int scWidth, scHeight;
    static int resizeEventWatcher(void* data, SDL_Event* event);
public:
    SDL_Renderer* renderer;
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