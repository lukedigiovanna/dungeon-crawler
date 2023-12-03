#include "AnimationManager.h"

#include <stdexcept>

AnimationManager::AnimationManager() {

}

void AnimationManager::registerAnimation(std::string id, std::shared_ptr<Animation> spriteDeck) {
    if (spriteDecks.find(id) != spriteDecks.end()) {
        throw std::runtime_error("AnimationManager::registerAnimation: Animation id '" + id + "' already used");
    }
    spriteDecks[id] = spriteDeck;
}

std::shared_ptr<Animation> AnimationManager::getAnimation(std::string id) const {
    auto f = spriteDecks.find(id);
    if (f == spriteDecks.end()) {
        throw std::runtime_error("AnimationManager::getAnimation: No animation found with id '" + id + "'");
    }
    return f->second;
}