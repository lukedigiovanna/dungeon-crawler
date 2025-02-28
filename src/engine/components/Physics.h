#pragma once

#include "Component.h"
#include "../utils/Math.h"

class Physics: public Component {
public:
    // Rate of movement
    math::vec2 velocity;
    // Rate of rotation
    float angularVelocity;
    // Proportion of velocity removed per second as e^{-D}
    // Example: D = 1, then e^{-1}=0.37 is removed per second
    // Higher values correspond to more rigid movements
    // While lower values glide more
    float dragCoefficient;
    // Magnitude of gravity
    float gravity;
    // Unit vector of gravity direction (defaults to "down")
    math::vec2 gravityDirection;
    // How much velocity is reflected on collision (1.0f should bounce back to same height, 0.0f should have no bounce)
    float bounciness;

    Physics();

    void update(float dt) override;
};