#include "Animation.h"

#include <cmath>

Animation::Animation(float fps) : 
    fps(fps) {

}

float Animation::getFps() const {
    return this->fps;
}

void Animation::addFrame(const Sprite* sprite) {
    this->sprites.push_back(sprite);
}

void Animation::addFrame(std::shared_ptr<SpriteManager> spriteManager, std::string const& spriteId) {
    addFrame(spriteManager->getSprite(spriteId));
}

const Sprite* Animation::getFrame(int frameIndex) const {
    return this->sprites[frameIndex];
}

size_t Animation::getNumberOfFrames() const {
    return this->sprites.size();
}
