#include "GameObject.h"

GameObject::GameObject() : position{0.0f, 0.0f}, scale{1.0f, 1.0f} {

}

void GameObject::setRendererComponent(std::shared_ptr<RendererComponent> rendererComponent) {
    this->rendererComponent = rendererComponent;
}

void GameObject::render(Window* window, float x, float y, float width, float height) const {
    if (this->rendererComponent) {
        this->rendererComponent->render(window, x, y, width, height);
    }
}

bool GameObject::hasRenderer() const {
    return this->rendererComponent.get() != nullptr;
}

void GameObject::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

std::shared_ptr<Scene> GameObject::getScene() const {
    std::shared_ptr<Scene> scenePtr = this->scene.lock();
    if (scenePtr == nullptr)
        throw std::runtime_error("Cannot acquire scene from a GameObject which is not in a scene");
    return scenePtr;
}

void GameObject::update(float dt) {
    for (const auto & [ typeId, component] : this->components) {
        component->update(dt);
    }
}