#include "AnimatedSpriteRenderer.h"

#include <utility>

AnimatedSpriteRenderer::AnimatedSpriteRenderer(std::unique_ptr<AnimationController> animationController) :
    controller(std::move(animationController)) {

}

void AnimatedSpriteRenderer::update(float dt) {

}

void AnimatedSpriteRenderer::render(Window* window, float x, float y, float width, float height) const {

}