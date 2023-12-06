#include "SpriteAnimator.h"

#include "../GameObject.h"
#include "../Scene.h"
#include "../utils/Math.h"

#include "renderers/SpriteRenderer.h"

#include <typeinfo>

#include <iostream>

SpriteAnimator::SpriteAnimator(std::string const& animationId) 
    : animationId(animationId), shouldPlay(true), loopType(LOOP_CONTINUOUSLY) {
}

void SpriteAnimator::setAnimation(std::string const& animationId) {
    if (!initialized) {
        throw std::runtime_error("SpriteAnimator::setAnimation: Cannot set sprite animation on SpriteAnimator which has not been initialized");
    }
    
    if (this->animationId == animationId) {
        return;
    }

    std::shared_ptr<AnimationManager> animManager = getGameObject()->getScene()->getManagers()->animationManager;
    animation = animManager->getAnimation(animationId);
    this->animationId = animationId;
    timer = 0.0f;
    currentFrame = 0;
    this->spriteRenderer->setSprite(animation->getFrame(currentFrame));
}

void SpriteAnimator::seek(float timeOffset) {
    timer += timeOffset;
    int numFrames = static_cast<int>(timer / (1.0 / animation->getFps()));
    currentFrame = (currentFrame + numFrames) % animation->getNumberOfFrames();
    timer = std::fmod(timer, 1.0f / animation->getFps());
}

void SpriteAnimator::init() {
    std::shared_ptr<AnimationManager> animManager = getGameObject()->getScene()->getManagers()->animationManager;
    animation = animManager->getAnimation(animationId);
    
    RendererComponent* rc = &getGameObject()->getRendererComponent();
    // Assert that the renderer component is a sprite renderer
    this->spriteRenderer = dynamic_cast<SpriteRenderer*>(rc);

    if (this->spriteRenderer == nullptr) {
        throw std::runtime_error("SpriteAnimator::init: The renderer component attached to this object is not a sprite renderer");
    }

    initialized = true;
}

void SpriteAnimator::stop() {
    pause();
    reset();
}

void SpriteAnimator::pause() {
    shouldPlay = false;
}

void SpriteAnimator::resume() {
    shouldPlay = true;
}

void SpriteAnimator::reset() {
    timer = 0;
    currentFrame = 0;
}

void SpriteAnimator::loop() {
    timer = 0;
    currentFrame = 0;
    loopType = LOOP_CONTINUOUSLY;
    shouldPlay = true;
}

void SpriteAnimator::loopOnce() {
    timer = 0;
    currentFrame = 0;
    loopType = LOOP_ONCE;
    shouldPlay = true;
    loopOnceCallbackFunction = []() {}; // Do nothing function
}

void SpriteAnimator::loopOnce(std::function<void()> callback) {
    loopOnce();
    loopOnceCallbackFunction = callback;
}

void SpriteAnimator::update(float dt) {
    if (shouldPlay) {
        timer += dt;
        float fps = animation->getFps();
        if (timer >= 1.0f / fps) {
            timer = std::fmod(timer, 1.0f / fps);
            currentFrame = (currentFrame + 1) % animation->getNumberOfFrames();
            this->spriteRenderer->setSprite(animation->getFrame(currentFrame));
            if (loopType == LOOP_ONCE && currentFrame == 0) { // i.e. we looped
                shouldPlay = false;
                loopOnceCallbackFunction();
            }
        }
    }
}