#pragma once

#include "UIElement.h"

class ContainerElement: public UIElement {
private:
    void renderElement() const override;
public:
    ContainerElement(const math::vec2& position, const math::vec2& dimension);
};
