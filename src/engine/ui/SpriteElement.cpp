#include "SpriteElement.h"

#include "../Engine.h"

SpriteElement::SpriteElement(const Sprite* sprite) :
    sprite(sprite),
    color(gfx::COLOR_WHITE) {

}

void SpriteElement::render() const {
    if (sprite) {
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui");
        shader.use();
        sprite->texture->bind(shader, "tex");
        shader.setVec4("color", color.r, color.g, color.b, color.a);
    }
}