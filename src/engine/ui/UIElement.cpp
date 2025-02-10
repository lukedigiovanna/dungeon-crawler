#include "UIElement.h"

UIElement::UIElement() : UIElement(0, 0) {

}

UIElement::UIElement(float x, float y) :
    transform{math::vec2{x, y}, math::vec2{1, 1}, 0},
    tag("untagged") {

}

UIElement* UIElement::getElementByTag(const std::string& tag) {
    if (this->tag == tag) {
        return this;
    }
    for (const auto& child : children) {
        auto find = child->getElementByTag(tag);
        if (find) {
            return find;
        }
    }
    return nullptr;
}

void UIElement::addChild(std::unique_ptr<UIElement> element) {
    element->parent = this;
    children.push_back(std::move(element));
}

math::vec2 UIElement::getComputedPosition() const {
    math::vec2 anchorPosition = {0, 0};
    
}

void UIElement::render() const {
    for (const auto& child : children) {
        child->render();
    }
}