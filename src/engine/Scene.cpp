#include "Scene.h"

Scene::Scene() {

}

void Scene::addGameObject(std::weak_ptr<GameObject> gameObject) {
    this->gameObjects.push_back(gameObject);
}