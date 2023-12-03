#pragma once

#include "../../engine/components/Component.h"
#include "../../engine/components/Physics.h"
#include "../../engine/components/SpriteAnimator.h"

class PlayerMovement: public Component {
private:
    std::shared_ptr<Physics> physics;
    std::shared_ptr<SpriteAnimator> animator;
    float speed;
public:
    PlayerMovement(float speed);

    void init() override;
    void update(float dt) override;
};