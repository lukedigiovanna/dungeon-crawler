#include "UIElement.h"

#include "../Engine.h"
#include "../Window.h"

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
    const Window* window = Engine::getSingleton()->getWindow();
    math::vec2 relativeOffset = transform.position - anchor;
    math::vec2 anchorPositionOnScreen = {
        anchor.x / Window::DEFAULT_WIDTH * window->width(),
        anchor.y / Window::DEFAULT_HEIGHT * window->height()
    };
    return anchorPositionOnScreen + relativeOffset;
}

void UIElement::setAnchor(AnchorPreset anchorPreset) {
    switch (anchorPreset) {
    case AnchorPreset::TOP_LEFT:
        anchor = { 0.0f, 0.0f }; break;
    case AnchorPreset::TOP_CENTER:
        anchor = { Window::DEFAULT_WIDTH / 2.0f, 0.0f }; break;
    case AnchorPreset::TOP_RIGHT:
        anchor = { Window::DEFAULT_WIDTH, 0.0f }; break;
    case AnchorPreset::CENTER_LEFT:
        anchor = { 0.0f, Window::DEFAULT_HEIGHT / 2.0f }; break;
    case AnchorPreset::CENTER:
        anchor = { Window::DEFAULT_WIDTH / 2.0f, Window::DEFAULT_HEIGHT / 2.0f }; break;
    case AnchorPreset::CENTER_RIGHT:
        anchor = { Window::DEFAULT_WIDTH, Window::DEFAULT_HEIGHT / 2.0f }; break;
    case AnchorPreset::BOTTOM_LEFT:
        anchor = { 0.0f, Window::DEFAULT_HEIGHT }; break;
    case AnchorPreset::BOTTOM_CENTER:
        anchor = { Window::DEFAULT_WIDTH / 2.0f, Window::DEFAULT_HEIGHT }; break;
    case AnchorPreset::BOTTOM_RIGHT:
        anchor = { Window::DEFAULT_WIDTH, Window::DEFAULT_HEIGHT }; break;
    }
}

void UIElement::render() const {
    for (const auto& child : children) {
        child->render();
    }
}