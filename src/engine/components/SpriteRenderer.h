#pragma once

#include "RendererComponent.h"
#include "../utils/AnimationController.h"
#include "../managers/SpriteManager.h"

class SpriteRenderer: public RendererComponent {
private:
    std::string spriteId;
    const Sprite* sprite = nullptr;
    std::unique_ptr<AnimationController> animationController = nullptr;
public:
    SpriteRenderer(std::string spriteId);
    SpriteRenderer(std::unique_ptr<AnimationController> animationController);
    
    void init() override;
    void render(Window* window, float x, float y, float width, float height) const override;
};