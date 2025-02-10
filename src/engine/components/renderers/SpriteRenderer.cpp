#include "SpriteRenderer.h"

#include "../../GameObject.h"
#include "../../Scene.h"
#include "../../Engine.h"
#include "../../utils/Math.h"
#include "../../utils/meshes.h"
#include "../../managers/Managers.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(std::string const& spriteId) : spriteId(spriteId), color{1.0f, 1.0f, 1.0f, 1.0f} {

}

SpriteRenderer::SpriteRenderer(std::string const& spriteId, gfx::color const& color) : spriteId(spriteId), color(color) {

}

void SpriteRenderer::setSprite(std::string const& spriteId) {
    if (!initialized) {
        throw std::runtime_error("SpriteRenderer::setSprite: Cannot set the sprite of a sprite renderer which hasn't been initialized");
    }
    SpriteManager& spriteManager = Engine::getSingleton()->getManagers()->spriteManager();
    this->sprite = spriteManager.getSprite(spriteId);
}

void SpriteRenderer::setSprite(const Sprite* sprite) {
    if (!initialized) {
        throw std::runtime_error("SpriteRenderer::setSprite: Cannot set the sprite of a sprite renderer which hasn't been initialized");
    }
    this->sprite = sprite;
}

void SpriteRenderer::init() {
    SpriteManager& spriteManager = Engine::getSingleton()->getManagers()->spriteManager();
    sprite = spriteManager.getSprite(spriteId);
    initialized = true;
}

void SpriteRenderer::render(Shader& shader) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(obj->transform.position.x, obj->transform.position.y, 0.0f));
    trans = glm::rotate(trans, math::degToRad(obj->transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(obj->transform.scale.x, obj->transform.scale.y, 1.0f));
    shader.setMatrix4("model", trans);
    shader.setVec4("objectColor", glm::vec4(color.r, color.g, color.b, color.a));
    sprite->render(shader);
}