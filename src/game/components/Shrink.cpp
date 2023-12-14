#include "Shrink.h"

#include "../../engine/GameObject.h"

void Shrink::init() {
    lifetime = getGameObject()->getComponent<Lifetime>();
    // light = getGameObject()->getComponent<LightSource>();
}

void Shrink::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    float s = 0.5f - 0.5f * lifetime->getAge() / lifetime->getLifetime();
    obj->transform.scale = { s, s };
    // light->luminance = 0.25f - 0.25f * lifetime->getAge() / lifetime->getLifetime();
}