#include "Physics.h"

#include "../GameObject.h"

Physics::Physics() : 
    velocity{0.0f, 0.0f}, 
    angularVelocity(0.0f),
    innateDragCoefficient(0.0f),
    gravity(0.0f),
    gravityDirection{0.0f, -1.0f},
    bounciness(0.5f) {
};

void Physics::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    // Apply gravity
    velocity += gravityDirection * gravity * dt;

    // Update position
    obj->transform.position += velocity * dt;
    obj->transform.rotation += angularVelocity * dt;

    // Apply drag
    float percentToRemove = dt * innateDragCoefficient;
    velocity *= (1.0f - percentToRemove);
    if (velocity.magnitude() < 1e-4) {
        velocity = { 0, 0 };
    }
}