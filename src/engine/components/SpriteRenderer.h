#pragma once

#include "RendererComponent.h"

class SpriteRenderer: public RendererComponent {
private:
    std::string spriteId;
    SDL_Texture* texture;
public:
    SpriteRenderer(std::string spriteId);
    
    void init() override;
    void render(Window* window, float x, float y, float width, float height) const override;
};