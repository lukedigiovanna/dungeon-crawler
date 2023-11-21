#include "GameObject.h"

#include "Scene.h"

#include <utility>

GameObject::GameObject() : position{0.0f, 0.0f}, scale{1.0f, 1.0f}, rotation(0.0f) {

}

void GameObject::setRendererComponent(std::unique_ptr<RendererComponent> rendererComponent) {
    this->rendererComponent = std::move(rendererComponent);
    this->rendererComponent->setGameObject(shared_from_this());
    if (isInScene()) {
        this->rendererComponent->init();
    }
}

void GameObject::render(Window* window, float x, float y, float width, float height) const {
    if (this->rendererComponent) {
        this->rendererComponent->render(window, x, y, width, height);
    }
}

bool GameObject::hasRenderer() const {
    return this->rendererComponent != nullptr;
}

void GameObject::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

std::shared_ptr<Scene> GameObject::getScene() const {
    std::shared_ptr<Scene> scenePtr = this->scene.lock();
    if (scenePtr == nullptr)
        throw std::runtime_error("GameObject::getScene: Cannot acquire scene from a GameObject which is not in a scene");
    return scenePtr;
}

bool GameObject::isInScene() const {
    std::shared_ptr<Scene> scene = this->scene.lock();
    return scene != nullptr;
}

void GameObject::init() {
    if (!isInScene()) {
        throw std::runtime_error("GameObject::init: Cannot initialize a GameObject which is not in a scene");
    }
    for (const auto & [ typeId, component] : this->components) {
        component->init();
    }
    if (this->rendererComponent)
        this->rendererComponent->init();
}

void GameObject::update(float dt) {
    for (const auto & [ typeId, component] : this->components) {
        component->update(dt);
    }
}

void GameObject::destroy() {
    std::shared_ptr<Scene> scene = getScene();
    scene->destroyGameObject(shared_from_this());
}