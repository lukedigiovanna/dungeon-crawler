#include "Canvas.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Engine.h"

#include "ContainerElement.h"

Canvas::Canvas() {
    // The root is a container across the whole screen
    root = std::make_unique<ContainerElement>(
        math::vec2{ 0, 0 },
        math::vec2{ Window::DEFAULT_WIDTH, Window::DEFAULT_HEIGHT }
    );
    root->setAlignment(PositionAlignment::POSITION_TOP_LEFT);
    root->setTag("root");
}

UIElement* Canvas::getElementByTag(const std::string& tag) const {
    return root->getElementByTag(tag);
}

void Canvas::addElement(std::unique_ptr<UIElement> element) {
    root->addChild(std::move(element));
}

void Canvas::render() const {
    root->recomputePositionAndDimension();
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