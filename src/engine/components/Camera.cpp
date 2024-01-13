#include "Camera.h"
#include "Lifetime.h"
#include "LightSource.h"
#include "../Scene.h"
#include "../Engine.h"
#include "../utils/Shader.h"
#include "../utils/meshes.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <math.h>
#include <string>

#define MAX_NUM_LIGHTS 15

Camera::Camera() : scale(10.0f), rotation(0.0f), windowDimension{640.0f, 480.0f} {
    aspectRatio = windowDimension.x / windowDimension.y;
}

void Camera::init() {
    std::shared_ptr<Lifetime> lifetime = std::make_shared<Lifetime>();
    this->getGameObject()->addComponent(lifetime); 
}

void Camera::update(float dt) {
    
}

math::vec2 Camera::screenPositionToWorldPosition(math::vec2 screenPosition) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    math::vec2 normPos = screenPosition / windowDimension;
    float worldWidth = this->scale;
    float worldHeight = 1.0f / aspectRatio * worldWidth;
    float cameraLeftWorldX = obj->transform.position.x - worldWidth / 2.0f,
          cameraTopWorldY = obj->transform.position.y + worldHeight / 2.0f;
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

    float cameraLeftWorldX = obj->transform.position.x - worldWidth / 2.0f,
          cameraRightWorldX = obj->transform.position.x + worldWidth / 2.0f,
          cameraBottomWorldY = obj->transform.position.y - worldHeight / 2.0f,
          cameraTopWorldY = obj->transform.position.y + worldHeight / 2.0f;

    math::Rectangle viewport = {
        cameraLeftWorldX, cameraTopWorldY,
        cameraRightWorldX - cameraLeftWorldX,
        cameraTopWorldY - cameraBottomWorldY
    };

    glm::mat4 proj = glm::ortho(cameraLeftWorldX, cameraRightWorldX, cameraBottomWorldY, cameraTopWorldY);
    glm::vec3 thisPos = glm::vec3(obj->transform.position.x, obj->transform.position.y, -1.0f);
    // glm::mat4 view = glm::lookAt(thisPos, thisPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0));
    // glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    // glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -thisPos);

    glm::mat4 view(1.0f);

    Shader& shader = Engine::getSingleton()->getManagers()->shaderManager->getShader("_scene");

    shader.use();

    shader.setVec2("screenSize", window->width(), window->height());

    shader.setMatrix4("projection", proj);
    shader.setMatrix4("view", view);

    shader.setVec3("ambientLight", 0.1f, 0.1f, 0.1f);

    int lightIndex = 0;
    for (auto gameObject : gameObjects) {
        if (gameObject->hasComponent<LightSource>()) {
            std::shared_ptr<LightSource> ls = gameObject->getComponent<LightSource>();
            ls->set(shader, lightIndex++, proj);
            if (lightIndex >= MAX_NUM_LIGHTS) {
                break;
            }
        }
    }
    shader.setInt("numLights", lightIndex);

    if (scene->hasTilemap()) {
        scene->getTilemap().render(shader, viewport);
    }

    for (auto gameObject : gameObjects) {
        gameObject->render(shader);
    }
}