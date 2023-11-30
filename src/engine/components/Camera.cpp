#include "Camera.h"
#include "Lifetime.h"
#include "../Scene.h"
#include "../utils/Shader.h"
#include "../utils/meshes.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <math.h>

Camera::Camera() : scale(10.0f), rotation(0.0f), windowDimension{640.0f, 480.0f} {
    aspectRatio = windowDimension.x / windowDimension.y;
}

void Camera::init() {
    std::shared_ptr<Lifetime> lifetime = std::make_shared<Lifetime>();
    this->getGameObject()->addComponent(lifetime); 
}

void Camera::update(float dt) {
    
}

vec2 Camera::screenPositionToWorldPosition(vec2 screenPosition) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    vec2 normPos = screenPosition / windowDimension;
    float worldWidth = this->scale;
    float worldHeight = 1.0f / aspectRatio * worldWidth;
    float cameraLeftWorldX = obj->position.x - worldWidth / 2.0f,
          cameraTopWorldY = obj->position.y + worldHeight / 2.0f;
    float worldX = cameraLeftWorldX + normPos.x * worldWidth,
          worldY = cameraTopWorldY - normPos.y * worldHeight;
    return { worldX, worldY };
}

void Camera::render(Window* window) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    std::shared_ptr<GameObject> obj = getGameObject();
    std::shared_ptr<Scene> scene = obj->getScene();
    auto gameObjects = scene->getGameObjects();

    windowDimension = { static_cast<float>(window->width()), static_cast<float>(window->height()) };
    aspectRatio = windowDimension.x / windowDimension.y;
    float worldWidth = this->scale;
    float worldHeight = 1.0f / aspectRatio * worldWidth;

    float cameraLeftWorldX = obj->position.x - worldWidth / 2.0f,
          cameraRightWorldX = obj->position.x + worldWidth / 2.0f,
          cameraBottomWorldY = obj->position.y - worldHeight / 2.0f,
          cameraTopWorldY = obj->position.y + worldHeight / 2.0f;

    glm::mat4 proj = glm::ortho(cameraLeftWorldX, cameraRightWorldX, cameraBottomWorldY, cameraTopWorldY);
    glm::vec3 thisPos = glm::vec3(obj->position.x, obj->position.y, -1.0f);
    // glm::mat4 view = glm::lookAt(thisPos, thisPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0));
    // glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    // glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -thisPos);

    glm::mat4 view(1.0f);

    std::shared_ptr<Shader> shader = scene->getManagers()->shaderManager->getShader("_scene");
    
    shader->use();

    shader->setMatrix4("projection", proj);
    shader->setMatrix4("view", view);

    shader->setVec2("light.position", 0.0f, 0.0f);
    shader->setFloat("light.luminance", 0.6f);
    shader->setVec3("light.color", 1.0f, 1.0f, 1.0f);

    for (auto gameObject : gameObjects) {
        gameObject->render(shader);
    }
}