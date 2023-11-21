#pragma once

#include "RendererComponent.h"

class SpriteRenderer: public RendererComponent {
private:
    SDL_Texture* texture;
public:
    SpriteRenderer();
    void render(Window* window, float x, float y, float width, float height) const override;
};