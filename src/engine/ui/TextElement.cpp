#include "TextElement.h"

#include "../Engine.h"

TextElement::TextElement(const Font* font, const gfx::color& color, TextAlignment alignment, float size, const std::string& text) : 
    font(font), 
    color(color),
    alignment(alignment),
    size(size),
    text(text) {

}

void TextElement::renderElement() const {
    if (font) {
        Shader& shader = Engine::getSingleton()->getManagers()->shaderManager().getShader("_ui_text");
        math::vec2 position = getComputedPosition();
        float scale = size / 20.0f;
        ScaleMode sm = getScaleMode();
        if (sm == ScaleMode::SCALE_WITH_WIDTH) {
            scale *= Engine::getSingleton()->getWindow()->width() / Window::DEFAULT_WIDTH;
        }
        else if (sm == ScaleMode::SCALE_WITH_HEIGHT) {
            scale *= Engine::getSingleton()->getWindow()->height() / Window::DEFAULT_HEIGHT;
        }
        font->renderText(shader, text, color, alignment, position.x, position.y, scale);
    }
}