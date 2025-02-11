#include "TextElement.h"

#include "../Engine.h"

TextElement::TextElement(const Font* font, const gfx::color& color, const std::string& text) : 
    font(font), 
    color(color),
    text(text) {

}

void TextElement::render() const {
    if (font) {
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui");
        math::vec2 computed = getComputedPosition();
        font->renderText(shader, text, color, computed.x, computed.y, 1.0f);
    }
    UIElement::render();
}