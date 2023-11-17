#include "Component.h"

Component::Component() {
    
}

void Component::setGameObject(std::shared_ptr<GameObject> gameObject) {
    this->gameObject = gameObject;
}