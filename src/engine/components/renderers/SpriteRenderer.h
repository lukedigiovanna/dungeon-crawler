#pragma once

#include "RendererComponent.h"
#include "../../utils/AnimationController.h"
#include "../../managers/SpriteManager.h"

class SpriteRenderer: public RendererComponent {
private:
    std::string spriteId;
    const Sprite* sprite = nullptr;
public:
    SpriteRenderer(std::string spriteId);
    
    void init() override;
    void render(std::shared_ptr<Shader> shader) const override;
};