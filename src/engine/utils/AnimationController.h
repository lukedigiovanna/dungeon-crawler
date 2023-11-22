#pragma once

#include "Animation.h"

#include <unordered_map>
#include <string>

class AnimationController {
private:
    std::weak_ptr<Animation> currentAnimation;
    std::unordered_map<std::string, std::shared_ptr<Animation>> animations;
public:
    // AnimationController();

    // void registerAnimation(std::string animId, std::shared_ptr<Animation> animation);
    // void setAnimation(std::string animId);
};