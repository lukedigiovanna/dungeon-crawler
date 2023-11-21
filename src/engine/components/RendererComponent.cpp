#include "RendererComponent.h"

RendererComponent::RendererComponent() {

}

std::shared_ptr<GameObject> RendererComponent::getGameObject() const {
    std::shared_ptr<GameObject> obj = this->gameObject.lock();
    if (obj == nullptr) {
        throw std::runtime_error("Cannot get GameObject on renderer component that is not attached to a GameObject");
    }
    return obj;
}

void RendererComponent::setGameObject(std::shared_ptr<GameObject> gameObject) {
    this->gameObject = gameObject;
}

void RendererComponent::render(Window* window, float x, float y, float width, float height) const {
    
}