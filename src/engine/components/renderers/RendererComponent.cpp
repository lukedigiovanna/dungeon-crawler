#include "RendererComponent.h"
#include "../../GameObject.h"
#include "../../Scene.h"

#include <stdexcept>

RendererComponent::RendererComponent() {

}

RendererComponent::~RendererComponent() {

}

Shader& RendererComponent::getShader(std::string const& shaderId) const {
    return getGameObject()->getScene()->getManagers()->shaderManager->getShader(shaderId);
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

void RendererComponent::render(Shader& shader) const {
    
}

void RendererComponent::update(float dt) {
    
}

void RendererComponent::init() {
    
}