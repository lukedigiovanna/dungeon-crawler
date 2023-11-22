#include "InputManager.h"

InputManager::InputManager() : mousePosition{0.0f, 0.0f}, mouseIsDown(false) {

}

void InputManager::update(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        down[event.key.keysym.sym] = true;
        pressed[event.key.keysym.sym] = true;
    }
    else if (event.type == SDL_KEYUP) {
        down[event.key.keysym.sym] = false;
        pressed[event.key.keysym.sym] = false;
    }
    else if (event.type == SDL_MOUSEMOTION) {
        mousePosition = { static_cast<float>(event.motion.x), static_cast<float>(event.motion.y) };
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        mouseIsDown = true;
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        mouseIsDown = false;
    }
}

bool InputManager::isKeyDown(SDL_Keycode key) const {
    auto f = down.find(key);
    if (f == down.end()) {
        return false;
    }
    return f->second;
}

bool InputManager::isKeyPressed(SDL_Keycode key) {
    auto f = pressed.find(key);
    if (f == down.end()) {
        return false;
    }
    bool retVal = f->second;
    pressed[key] = false;
    return retVal;
}

vec2 InputManager::getMousePosition() const {
    return this->mousePosition;
}

bool InputManager::isMouseDown() const {
    return this->mouseIsDown;
}