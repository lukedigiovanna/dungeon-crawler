#include "Physics.h"

#include "../GameObject.h"

Physics::Physics() : 
    velocity{0.0f, 0.0f}, 
    angularVelocity(0.0f),
    innateDragCoefficient(0.0f) {
};

void Physics::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    // Update position
    obj->position += velocity * dt;
    obj->rotation += angularVelocity * dt;

    // Apply drag
    float percentToRemove = dt * innateDragCoefficient;
    velocity *= (1.0f - percentToRemove);
}