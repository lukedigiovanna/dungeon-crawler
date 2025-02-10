#include "TextElement.h"

#include "../Engine.h"

TextElement::TextElement(const Font* font, const std::string& text) : font(font), text(text) {

}

void TextElement::render() const {
    if (font) {
        Shader& textShader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_text");
        font->renderText(textShader, text, transform.position.x, transform.position.y, 1.0f);
    }
    UIElement::render();
}