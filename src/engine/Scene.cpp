#include "Scene.h"
#include "components/Lifetime.h"

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
    std::shared_ptr<Lifetime> lifetime = std::make_shared<Lifetime>();
    cameraObj->addComponent(lifetime);
    this->addGameObject(cameraObj);
    
    std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
    go->position.x = 2.0f;
    go->position.y = 2.0f;
    this->addGameObject(go);
}

void Scene::update(float dt) {
    for (auto gameObject : this->gameObjects) {
        gameObject->update(dt);
    }
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

    this->camera->render(window);
}