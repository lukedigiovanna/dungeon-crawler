#pragma once

#include "Component.h"
#include <SDL.h>

class Camera: public Component {
private:
    float zoomScale;
public:
    Camera();

    void render(SDL_Renderer* renderer) const;
};