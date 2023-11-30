#pragma once

#include "RendererComponent.h"
#include "../../utils/AnimationController.h"
#include "../../utils/Graphics.h"
#include "../../managers/SpriteManager.h"

class SpriteRenderer: public RendererComponent {
private:
    std::string spriteId;
    const Sprite* sprite = nullptr;
public:
    gfx::color color;
    SpriteRenderer(std::string spriteId);
    SpriteRenderer(std::string spriteId, gfx::color const& color);
    
    void init() override;
    void render(std::shared_ptr<Shader> shader) const override;
};