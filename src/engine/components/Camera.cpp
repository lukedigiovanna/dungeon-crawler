#include "Camera.h"
#include "../Scene.h"

Camera::Camera() : zoomScale(1.0f) {}

void Camera::render(SDL_Renderer* renderer) const {
    // acquire all game objects
    std::shared_ptr<GameObject> obj = this->gameObject.lock();
    if (obj == nullptr)
        throw std::runtime_error("Cannot render from a camera not attached to a GameObject");

    std::shared_ptr<Scene> scene = obj->getScene();
    auto gameObjects = scene->getGameObjects();
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto gameObject : gameObjects) {
        SDL_FRect rect = { gameObject->position.x, gameObject->position.y, 10, 10 };
        SDL_RenderDrawRectF(renderer, &rect);
    }
}