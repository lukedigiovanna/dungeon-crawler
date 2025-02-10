#pragma once

#include <unordered_map>
#include <SDL.h>
#include "../utils/Math.h"

class InputManager {
private:
    std::unordered_map<SDL_Keycode, bool> down;
    std::unordered_map<SDL_Keycode, bool> pressed;

    math::vec2 mousePosition;
    bool mouseIsDown;
public:
    InputManager();
    InputManager(const InputManager&) = delete;

    void update(SDL_Event& event);

    bool isKeyDown(SDL_Keycode kc) const;
    bool isKeyPressed(SDL_Keycode kc);

    math::vec2 getMousePosition() const;
    bool isMouseDown() const;
};