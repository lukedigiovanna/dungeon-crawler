#include "ShapeRenderer.h"

#include "../../GameObject.h"
#include "../../Scene.h"
#include "../../utils/meshes.h"
#include "../../utils/Math.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

ShapeRenderer::ShapeRenderer(const Mesh* mesh, gfx::color color) : mesh(mesh), color(color) {

}

ShapeRenderer::~ShapeRenderer() {
    
}

void ShapeRenderer::render(Shader& shader) const {
    std::shared_ptr<GameObject> obj = getGameObject();
    glm::mat4 trans(1.0f);
    trans = glm::translate(trans, glm::vec3(obj->transform.position.x, obj->transform.position.y, 0.0f));
    trans = glm::rotate(trans, math::degToRad(obj->transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(obj->transform.scale.x, obj->transform.scale.y, 1.0f));
    shader.setMatrix4("model", trans);
    shader.setVec4("objectColor", glm::vec4(color.r, color.g, color.b, color.a));
    const Sprite* sprite = obj->getScene()->getManagers()->spriteManager->getSprite("white");
    sprite->texture->bind();
    mesh->render();
}