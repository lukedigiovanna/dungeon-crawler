#include "Scene.h"
#include "components/Lifetime.h"
#include "utils/meshes.h"

#include <glad/glad.h>
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

bool Scene::hasTilemap() const {
    return tilemap != nullptr;
}

void Scene::setTilemap(std::unique_ptr<Tilemap> tilemap) {
    this->tilemap = std::move(tilemap);
    this->tilemap->setScene(shared_from_this());
}

Tilemap& Scene::getTilemap() const {
    if (tilemap == nullptr) {
        throw std::runtime_error("Scene::getTilemap: Cannot get tilemap because there is no tilemap present.");
    }
    return *tilemap;
}

void Scene::setManagers(std::shared_ptr<Managers> managers) {
    this->managers = managers;
}

std::shared_ptr<Managers> Scene::getManagers() const {
    return managers;
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

    this->destroyGameObjectQueue.clear();

    // Update game objects
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
    this->camera->render(window);
}

std::shared_ptr<Camera> Scene::getCamera() const {
    return this->camera;
}