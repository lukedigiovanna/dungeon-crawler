#include "Scene.h"

Scene::Scene() {
    // Do not construct any part of the scene prior to full construction of a scene
    // This is to ensure it is managed by a shared ptr before any calls to
    // addGameObject
}

void Scene::init() {
    // Every scene requires a camera on initialization
    std::shared_ptr<GameObject> cameraObj = std::make_shared<GameObject>();
    this->camera = std::make_shared<Camera>();
    cameraObj->addComponent(camera);
    this->addGameObject(cameraObj);
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObject->setScene(shared_from_this());
    this->gameObjects.push_back(gameObject);
}

std::vector<std::shared_ptr<GameObject>> const& Scene::getGameObjects() const {
    return this->gameObjects;
}

void Scene::render(Window* window) const {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(window->renderer);

    this->camera->render(window->renderer);
}