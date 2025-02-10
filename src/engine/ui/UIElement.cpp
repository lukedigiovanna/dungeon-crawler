#include "UIElement.h"

UIElement::UIElement() : UIElement(0, 0) {

}

UIElement::UIElement(float x, float y) :
    transform{math::vec2{x, y}, math::vec2{1, 1}, 0},
    id("null") {

}

UIElement* UIElement::getElementById(const std::string& id) {
    if (this->id == id) {
        return this;
    }
    for (const auto& child : children) {
        auto find = child->getElementById(id);
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

void UIElement::render() const {
    for (const auto& child : children) {
        child->render();
    }
}