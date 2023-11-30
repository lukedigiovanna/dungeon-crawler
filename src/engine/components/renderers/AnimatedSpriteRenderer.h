#pragma once

#include "RendererComponent.h"
#include "../../utils/AnimationController.h"

class AnimatedSpriteRenderer: public RendererComponent {
private:
    std::unique_ptr<AnimationController> controller;
public:
    AnimatedSpriteRenderer(std::unique_ptr<AnimationController> animationController);

    void update(float dt) override;
    void render(std::shared_ptr<Shader> shader) const override;
};

