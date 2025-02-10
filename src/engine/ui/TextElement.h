#pragma once

#include "UIElement.h"

#include "../utils/Font.h"

class TextElement : public UIElement {
private:
    std::string text;
    const Font* font;
public:
    TextElement(const Font* font, const std::string& text);

    void render() const override;

    inline void setText(const std::string& text) {
        this->text = text;
    }

    inline const std::string& getText() const {
        return text;
    }

    inline void setFont(const Font* font) {
        this->font = font;
    }

    inline const Font* getFont() const {
        return font;
    }
};
