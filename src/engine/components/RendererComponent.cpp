#include "RendererComponent.h"

RendererComponent::RendererComponent() {

}

RendererComponent::~RendererComponent() {

}

std::shared_ptr<GameObject> RendererComponent::getGameObject() const {
    std::shared_ptr<GameObject> obj = this->gameObject.lock();
    if (obj == nullptr) {
        throw std::runtime_error("RendererComponent::getGameObject: Cannot get GameObject on renderer component that is not attached to a GameObject");
    }
    return obj;
}

void RendererComponent::setGameObject(std::shared_ptr<GameObject> gameObject) {
    this->gameObject = gameObject;
}

void RendererComponent::render(Window* window, float x, float y, float width, float height) const {
    
}

void RendererComponent::update(float dt) {
    
}

void RendererComponent::init() {
    
}