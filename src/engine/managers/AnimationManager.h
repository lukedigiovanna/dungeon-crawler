#pragma once

#include "../utils/Animation.h"

#include <unordered_map>
#include <string>

class AnimationManager {
private:
    std::unordered_map<std::string, std::shared_ptr<AnimationSpriteDeck>> spriteDecks;
public:
    AnimationManager();

    void registerAnimation(std::string id, std::shared_ptr<AnimationSpriteDeck> spriteDeck);
    std::shared_ptr<AnimationSpriteDeck> getAnimation(std::string id) const;
};