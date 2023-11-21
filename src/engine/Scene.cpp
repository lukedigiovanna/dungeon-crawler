#include "Scene.h"
#include "components/Lifetime.h"
#include "components/ShapeRenderer.h"
#include "components/RendererComponent.h"

#include <iostream>
#include <algorithm>

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

void Scene::setSpriteManager(std::shared_ptr<SpriteManager> spriteManager) {
    this->spriteManager = spriteManager;
}

std::shared_ptr<SpriteManager> Scene::getSpriteManager() const {
    return this->spriteManager;
}

void Scene::update(float dt) {
    // Manage addGameObject queue
    for (auto gameObject : this->addGameObjectQueue) {
        gameObject->setScene(shared_from_this());
        this->gameObjects.push_back(gameObject);
    }

    for (auto gameObject : this->addGameObjectQueue) {
        gameObject->init();
    }

    this->addGameObjectQueue.clear();

    // Manage destroyGameObject queue
    for (auto gameObject : this->destroyGameObjectQueue) {
        gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
    }

    for (auto gameObject : this->gameObjects) {
        gameObject->update(dt);
    }
}

void Scene::addGameObject(std::shared_ptr<GameObject> gameObject) {
    this->addGameObjectQueue.push_back(gameObject);
}

void Scene::destroyGameObject(std::shared_ptr<GameObject> gameObject) {
    this->destroyGameObjectQueue.push_back(gameObject);
}

std::vector<std::shared_ptr<GameObject>> const& Scene::getGameObjects() const {
    return this->gameObjects;
}

void Scene::render(Window* window) const {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255); // black
    SDL_RenderClear(window->renderer);

    this->camera->render(window);
}