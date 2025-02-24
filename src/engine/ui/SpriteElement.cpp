#include "SpriteElement.h"

#include "../Engine.h"

#include <glm/gtc/matrix_transform.hpp>

SpriteElement::SpriteElement(const Sprite* sprite) :
    sprite(sprite),
    color(gfx::COLOR_WHITE) {

}

void SpriteElement::render() const {
    if (sprite) {
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_sprite");
        shader.use();
        glm::mat4 trans(1.0f);
        trans = glm::translate(trans, glm::vec3(50.0f, 50.0f, 0.0f));
        trans = glm::rotate(trans, math::degToRad(45), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(50.0f, 50.0f, 1.0f));
        shader.setMatrix4("model", trans);
        shader.setVec4("color", color.r, color.g, color.b, color.a);
        sprite->render(shader);
    }
}