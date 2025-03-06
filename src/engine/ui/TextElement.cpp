#include "TextElement.h"

#include "../Engine.h"

TextElement::TextElement(const Font* font, const gfx::color& color, TextAlignment textAlignment, float size, const std::string& text) : 
    font(font), 
    color(color),
    textAlignment(textAlignment),
    size(size),
    text(text),
    lineSpacing(0) {
    transform.position = { 0, 0 };
    transform.scale = { 250, 48 };
}

// #include <glm/gtc/matrix_transform.hpp>
void TextElement::renderElement() const {
    if (!font) {
        return;
    }

    math::vec2 position = getComputedPosition();
    math::vec2 dimension = getComputedDimension();

    // Shader& sShader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_sprite");
    // sShader.use();
    // glm::mat4 trans(1.0f);
    // trans = glm::translate(trans, glm::vec3(position.x + dimension.x / 2, position.y + dimension.y / 2, 0.0f));
    // trans = glm::rotate(trans, math::degToRad(transform.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    // trans = glm::scale(trans, glm::vec3(dimension.x, dimension.y, 1.0f));
    // sShader.setMatrix4("model", trans);
    // sShader.setVec4("color", 1, 1, 1, 1);
    // const Sprite* sprite = Engine::getSingleton()->getManagers()->spriteManager().getSprite("minecraft30");
    // sprite->render(sShader);

    Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_text");
    float scale = size / Font::FONT_HEIGHT;
    ScaleMode sm = getScaleMode();
    if (sm == ScaleMode::SCALE_WITH_WIDTH) {
        scale *= Engine::getSingleton()->getWindow()->width() / Window::DEFAULT_WIDTH;
    }
    else if (sm == ScaleMode::SCALE_WITH_HEIGHT) {
        scale *= Engine::getSingleton()->getWindow()->height() / Window::DEFAULT_HEIGHT;
    }

    if (textAlignment == JUSTIFY_CENTER) {
        position.x += dimension.x / 2;
    }
    else if (textAlignment == JUSTIFY_RIGHT) {
        position.x += dimension.x;
    }

    // render line by line until the text doesn't fit anymore
    float lineHeight = size + lineSpacing;
    int maxLines = static_cast<int>(dimension.y / lineHeight);
    int numLines = 0;
    int start = 0, count = 1;
    while (numLines + 1 <= maxLines && start + count < text.size()) {
        while (start + count <= text.size() && 
               font->textWidth(text.substr(start, count), scale) <= dimension.x) {
            count++;
        }
        int startCount = count;
        // delete word until whitespace
        while (count > 0 && text[start + count] != ' ') count--;
        // delete whitespace
        while (count > 0 && text[start + count] == ' ') count--;
        if (count == 0) 
            count = startCount - 1;
        else
            count++;
        font->renderText(shader, text.substr(start, count), color, textAlignment, position.x, position.y + numLines * lineHeight, scale);
        numLines++;
        start += count;
        count = 1;
    }
}