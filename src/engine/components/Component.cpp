#include "Component.h"

#include <stdexcept>

Component::Component() {
    
}

void Component::setGameObject(std::shared_ptr<GameObject> gameObject) {
    this->gameObject = gameObject;
}

std::shared_ptr<GameObject> Component::getGameObject() const {
    std::shared_ptr<GameObject> obj = this->gameObject.lock();
    if (!obj) {
        throw std::runtime_error("Component::getGameObject: Cannot get a game object from a component not attched to one");
    }
    return obj;
}

void Component::update(float dt) {
    // Do nothing
}

void Component::init() {
    // Do nothing
}