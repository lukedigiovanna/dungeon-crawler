#include "Camera.h"
#include "../Scene.h"
#include "Lifetime.h"

#include <iostream>
#include <math.h>

Camera::Camera() : scale(10.0f) {}

void Camera::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    std::shared_ptr<Lifetime> lifetime = obj->getComponent<Lifetime>();
    float age = lifetime->getAge();
    obj->position.x = std::cosf(age) * 2.0f;
    obj->position.y = std::sinf(age) * 2.0f;
    this->scale = std::cosf(age) * 3 + 5;
}

void Camera::render(Window* window) const {
    // acquire all game objects
    std::shared_ptr<GameObject> obj = getGameObject();
    int scWidth = window->width();
    int scHeight = window->height();
    float aspectRatio = static_cast<float>(scWidth) / static_cast<float>(scHeight);
    float worldWidth = this->scale;
    float worldHeight = 1.0f / aspectRatio * worldWidth;

    float cameraLeftWorldX = obj->position.x - worldWidth / 2.0f,
          cameraRightWorldX = obj->position.x + worldWidth / 2.0f,
          cameraBottomWorldY = obj->position.y - worldHeight / 2.0f,
          cameraTopWorldY = obj->position.y + worldHeight / 2.0f;

    std::shared_ptr<Scene> scene = obj->getScene();
    auto gameObjects = scene->getGameObjects();

    for (auto gameObject : gameObjects) {
        // Validate gameObject has a renderer
        if (!gameObject->hasRenderer())
            continue;
        // Validate this object is in the view of the camera
        // Off left side
        if (gameObject->position.x + gameObject->scale.x / 2.0f < cameraLeftWorldX)
            continue;
        // Off right side
        if (gameObject->position.x - gameObject->scale.x / 2.0f > cameraRightWorldX)
            continue;
        // Off bottom side
        if (gameObject->position.y + gameObject->scale.y / 2.0f < cameraBottomWorldY)
            continue;
        // Off top side
        if (gameObject->position.y - gameObject->scale.y / 2.0f > cameraTopWorldY)
            continue;

        // Perform world -> screen coordinate transformation
        float wx = (gameObject->position.x - cameraLeftWorldX) / worldWidth,
              wy = (gameObject->position.y - cameraBottomWorldY) / worldHeight;
    
        float sx = wx * scWidth;
        float sy = scHeight - wy * scHeight;

        float sw = gameObject->scale.x / worldWidth * scWidth;
        float sh = gameObject->scale.y / worldHeight * scHeight;
    
        // printf("w (%.2f, %.2f) s (%.2f, %.2f)\n", wx, wy, sx, sy);

        gameObject->render(window, sx, sy, sw, sh);
    }
}