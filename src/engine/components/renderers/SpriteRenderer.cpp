#include "SpriteRenderer.h"

#include "../../GameObject.h"
#include "../../Scene.h"
#include "../../utils/Math.h"
#include "../../utils/meshes.h"
#include "../../managers/Managers.h"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer::SpriteRenderer(std::string spriteId) : spriteId(spriteId), color{1.0f, 1.0f, 1.0f, 1.0f} {

}

SpriteRenderer::SpriteRenderer(std::string spriteId, gfx::color const& color) : spriteId(spriteId), color(color) {

}

void SpriteRenderer::init() {
    std::shared_ptr<SpriteManager> spriteManager = this->getGameObject()->getScene()->getManagers()->spriteManager;
    this->sprite = spriteManager->getSprite(spriteId);
}

void SpriteRenderer::render(std::shared_ptr<Shader> shader) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(obj->position.x, obj->position.y, 0.0f));
    trans = glm::rotate(trans, degToRad(obj->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(obj->scale.x, obj->scale.y, 1.0f));
    shader->setMatrix4("model", trans);
    shader->setVec4("objectColor", glm::vec4(color.r, color.g, color.b, color.a));
    sprite->texture->bind();
    shader->setVec4("clipRect", sprite->clip);
    meshes::SQUARE->render();
}