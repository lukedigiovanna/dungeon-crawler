#include "ShapeRenderer.h"

#include "../../GameObject.h"
#include "../../utils/meshes.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

ShapeRenderer::ShapeRenderer(Shape shape, gfx::color color) : shape(shape), color(color) {

}

ShapeRenderer::~ShapeRenderer() {
    
}

void ShapeRenderer::render(std::shared_ptr<Shader> shader) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(obj->position.x, obj->position.y, 0.0f));
    trans = glm::scale(trans, glm::vec3(obj->scale.x, obj->scale.y, 1.0f));
    shader->setMatrix4("model", trans);
    shader->setVec4("objectColor", glm::vec4(color.r, color.g, color.b, color.a));
    meshes::SQUARE->render();
}