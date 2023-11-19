#include "GameObject.h"

GameObject::GameObject() : position{0.0f, 0.0f} {

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