#include "TextElement.h"

#include "../Engine.h"

TextElement::TextElement(const Font* font, const gfx::color& color, TextAlignment alignment, float size, const std::string& text) : 
    font(font), 
    color(color),
    alignment(alignment),
    size(size),
    text(text) {

}

void TextElement::render() const {
    if (font) {
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui");
        math::vec2 computed = getComputedPosition();
        font->renderText(shader, text, color, alignment, computed.x, computed.y, size / 20.0f);
    }
    UIElement::render();
}