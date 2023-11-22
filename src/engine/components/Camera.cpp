#include "Camera.h"
#include "../Scene.h"
#include "Lifetime.h"

#include <iostream>
#include <math.h>

Camera::Camera() : scale(10.0f), windowDimension{640.0f, 480.0f} {
    aspectRatio = windowDimension.x / windowDimension.y;
}

void Camera::init() {
    std::shared_ptr<Lifetime> lifetime = std::make_shared<Lifetime>();
    this->getGameObject()->addComponent(lifetime); 
}

void Camera::update(float dt) {
    std::shared_ptr<GameObject> obj = getGameObject();
    std::shared_ptr<Lifetime> lifetime = obj->getComponent<Lifetime>();
    float age = lifetime->getAge();
    this->scale = std::cosf(age) * 2 + 8;
}

vec2 Camera::screenPositionToWorldPosition(vec2 screenPosition) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    vec2 normPos = screenPosition / windowDimension;
    float worldWidth = this->scale;
    float worldHeight = 1.0f / aspectRatio * worldWidth;
    float cameraLeftWorldX = obj->position.x - worldWidth / 2.0f,
          cameraTopWorldY = obj->position.y + worldHeight / 2.0f;
    float worldX = normPos.x * worldWidth + cameraLeftWorldX,
          worldY = cameraTopWorldY - normPos.y * worldHeight;
    return { worldX, worldY };
}

void Camera::render(Window* window) {
    // acquire all game objects
    std::shared_ptr<GameObject> obj = getGameObject();
    windowDimension = { static_cast<float>(window->width()), static_cast<float>(window->height()) };
    aspectRatio = windowDimension.x / windowDimension.y;
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
    
        float sx = wx * windowDimension.x;
        float sy = windowDimension.y - wy * windowDimension.y;

        float sw = gameObject->scale.x / worldWidth * windowDimension.x;
        float sh = gameObject->scale.y / worldHeight * windowDimension.y;
    
        // printf("w (%.2f, %.2f) s (%.2f, %.2f)\n", wx, wy, sx, sy);

        gameObject->render(window, sx, sy, sw, sh);
    }
}