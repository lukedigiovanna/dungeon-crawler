#pragma once

#include "UIElement.h"

#include "../utils/Graphics.h"
#include "../utils/Sprite.h"

class SpriteElement: public UIElement {
private:
    const Sprite* sprite;
    gfx::color color;

    void renderElement() const override;
public:
    SpriteElement(const std::string& spriteId);
    SpriteElement(const Sprite* sprite);

};