#pragma once

#include "Component.h"
#include "../utils/Math.h"

class Physics: public Component {
public:
    vec2 velocity;
    float angularVelocity;
    float innateDragCoefficient;

    Physics();

    void update(float dt) override;
};