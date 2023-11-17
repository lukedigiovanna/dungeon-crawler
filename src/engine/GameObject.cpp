#include "GameObject.h"

GameObject::GameObject() {

}

void GameObject::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}