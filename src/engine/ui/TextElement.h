#pragma once

#include "UIElement.h"

#include "../utils/Font.h"

class TextElement : public UIElement {
private:
    std::string text;

    const Font* font;
    gfx::color color;
    TextAlignment alignment;
    float size;

    void renderElement() const override;
public:
    TextElement(const Font* font, const gfx::color& color, TextAlignment alignment, float size, const std::string& text);

    // Text elements can not have children
    void addChild(std::unique_ptr<UIElement> element) = delete;

    inline void setText(const std::string& text) {
        this->text = text;
    }

    inline const std::string& getText() const {
        return text;
    }

    inline void setColor(const gfx::color& color) {
        this->color = color;
    }

    inline gfx::color getColor() const {
        return color;
    }

    inline void setAlignment(TextAlignment alignment) {
        this->alignment = alignment;
    }

    inline TextAlignment getAlignment() const {
        return alignment;
    }

    inline void setFont(const Font* font) {
        this->font = font;
    }

    inline const Font* getFont() const {
        return font;
    }
};
