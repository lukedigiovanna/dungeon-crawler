#pragma once

#include "RendererComponent.h"
#include "../../utils/Graphics.h"
#include "../../managers/SpriteManager.h"

class SpriteRenderer: public RendererComponent {
private:
    std::string spriteId;
    const Sprite* sprite = nullptr;
    bool initialized = false;
public:
    gfx::color color;
    SpriteRenderer(std::string const& spriteId);
    SpriteRenderer(std::string const& spriteId, gfx::color const& color);
    
    // Can only be called after the renderer has been initialized
    void setSprite(std::string const& spriteId);
    void setSprite(const Sprite* sprite);

    void init() override;
    void render(Shader& shader) const override;
};