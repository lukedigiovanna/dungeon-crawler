#include "Spin.h"

#include "../../engine/GameObject.h"

void Spin::update(float dt) {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    obj->rotation += dt * 90.0f;
}