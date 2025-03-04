#include "SpriteElement.h"

#include "../Engine.h"

#include <glm/gtc/matrix_transform.hpp>

SpriteElement::SpriteElement(const Sprite* sprite) :
    sprite(sprite),
    color(gfx::COLOR_WHITE) {

}

SpriteElement::SpriteElement(const std::string& spriteId) :
    color(gfx::COLOR_WHITE) {
    SpriteManager& spriteManager = Engine::getSingleton()->getManagers()->spriteManager();
    sprite = spriteManager.getSprite(spriteId);
}

void SpriteElement::render() const {
    if (sprite) {
        math::vec2 position = getComputedPosition();
        math::vec2 dimension = getComputedDimension();
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_sprite");
        shader.use();
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(position.x + dimension.x / 2, position.y + dimension.y / 2, 0.0f));
        trans = glm::rotate(trans, math::degToRad(transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(dimension.x, dimension.y, 1.0f));
        shader.setMatrix4("model", trans);
        shader.setVec4("color", color.r, color.g, color.b, color.a);
        sprite->render(shader);
    }
    UIElement::render();
}