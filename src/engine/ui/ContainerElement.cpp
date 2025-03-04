#include "ContainerElement.h"

ContainerElement::ContainerElement(const math::vec2& position, const math::vec2& dimension) {
    this->transform.position = position;
    this->transform.scale = dimension;
}

void ContainerElement::renderElement() const {
    // Nothing to do
}