#include "Scene.h"

Scene::Scene() {
    // Every scene requires a camera on initialization
    std::shared_ptr<GameObject> cameraObj = std::make_shared<GameObject>();
    this->camera = std::make_shared<Camera>();
    cameraObj->addComponent(camera);
    this->addGameObject(this->camera);
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObject->setScene(shared_from_this());
    this->gameObjects.push_back(gameObject);
}

void Scene::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(window->renderer);
}