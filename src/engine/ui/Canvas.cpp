#include "Canvas.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Engine.h"

Canvas::Canvas() {
    root = std::make_unique<UIElement>();
}

UIElement* Canvas::getElementByTag(const std::string& tag) const {
    return root->getElementByTag(tag);
}

void Canvas::addElement(std::unique_ptr<UIElement> element) {
    root->addChild(std::move(element));
}

void Canvas::render() const {
    // Set up the UI shader first
    const Window* window = Engine::getSingleton()->getWindow();
    glm::mat4 projection = glm::ortho(
        0.0f, window->width(), window->height(), 0.0f
    );
    Shader& textShader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_text");
    textShader.use();
    textShader.setMatrix4("projection", projection);
    Shader& spriteShader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_sprite");
    spriteShader.use();
    spriteShader.setMatrix4("projection", projection);
    root->render();
}