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
    Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui");
    shader.use();
    const Window* window = Engine::getSingleton()->getWindow();
    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(window->width()), 
        static_cast<float>(window->height()), 0.0f
    );
    shader.setMatrix4("projection", projection);
    root->render();
}