#include "Scene.h"
#include "components/Lifetime.h"
#include "utils/meshes.h"

#include <iostream>
#include <typeinfo>
#include <algorithm>

#include <glad/glad.h>

Scene::Scene() : ambientLight{ 1.0f, gfx::COLOR_WHITE } {
    // Do not construct any part of the scene prior to full construction of a scene
    // This is to ensure it is managed by a shared ptr before any calls to
    // addGameObject
}

void Scene::init() {
    // Every scene requires a camera on initialization
    std::shared_ptr<GameObject> cameraObj = std::make_shared<GameObject>();
    camera = std::make_shared<Camera>();
    cameraObj->addComponent(camera);
    addGameObject(cameraObj);

    setup();

    initialized = true;
}

void Scene::setup() {
    
}

bool Scene::hasTilemap() const {
    return tilemaps.size() > 0;
}

void Scene::addTilemap(std::unique_ptr<Tilemap> tilemap) {
    tilemap->setScene(shared_from_this());
    tilemaps.push_back(std::move(tilemap));
}

std::vector<std::unique_ptr<Tilemap>>& Scene::getTilemaps() {
    return tilemaps;
}

void Scene::update(float dt) {
    // Manage addGameObject queue
    for (auto gameObject : addGameObjectQueue) {
        gameObject->setScene(shared_from_this());
        gameObjects.push_back(gameObject);
    }

    for (auto gameObject : addGameObjectQueue) {
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

void Scene::setAmbientLight(float luminance, gfx::color const& color) {
    setAmbientLightLuminance(luminance);
    setAmbientLightColor(color);
}

void Scene::setAmbientLightLuminance(float luminance) {
    if (luminance < 0 || luminance > 1) {
        throw std::runtime_error("Scene::setAmbientLightLuminance: Luminance must be within 0 and 1 (inclusive)");
    }
    ambientLight.luminance = luminance;
}

void Scene::setAmbientLightColor(gfx::color const& color) {
    ambientLight.color = color;
}

void Scene::render(Window* window) const {
    this->camera->render(window);
    canvas.render();
}

std::shared_ptr<Camera> Scene::getCamera() const {
    return this->camera;
}