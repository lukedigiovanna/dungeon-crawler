#include "Sprite.h"

#include "meshes.h"

#include <glad/glad.h>

void Sprite::render(Shader const& shader) const {
    texture->bind();
    shader.setVec4("clipRect", clip);
    meshes::SQUARE->render();
}