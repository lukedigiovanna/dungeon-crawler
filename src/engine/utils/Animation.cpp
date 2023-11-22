#include "Animation.h"

#include <cmath>

AnimationSpriteDeck::AnimationSpriteDeck() {

}

void AnimationSpriteDeck::addFrame(const Sprite* sprite) {
    this->sprites.push_back(sprite);
}

void AnimationSpriteDeck::addFrame(std::shared_ptr<SpriteManager> spriteManager, std::string spriteId) {
    addFrame(spriteManager->getSprite(spriteId));
}

const Sprite* AnimationSpriteDeck::getFrame(int frameIndex) const {
    return this->sprites[frameIndex];
}

size_t AnimationSpriteDeck::getSize() const {
    return this->sprites.size();
}

Animation::Animation(std::shared_ptr<AnimationSpriteDeck> spriteDeck, float fps) : 
    spriteDeck(spriteDeck),
    fps(fps) {

}

const Sprite* Animation::getCurrentFrame() const {
    return spriteDeck->getFrame(currentFrame);
}

void Animation::play() {
    if (!playing) {
        currentFrame = 0;
        timer = 0;
        playing = true;
    }
}

void Animation::update(float dt) {
    if (playing) {
        timer += dt;
        if (timer >= 1.0f / fps) {
            timer = std::fmod(timer, 1.0f / fps);
            currentFrame = (currentFrame + 1) % spriteDeck->getSize();
        }
    }
}
