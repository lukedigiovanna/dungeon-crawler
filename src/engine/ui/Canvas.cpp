#include "Canvas.h"

Canvas::Canvas() {
    root = std::make_unique<UIElement>();
}

UIElement* Canvas::getElementByTag(const std::string& tag) const {
    return root->getElementByTag(tag);
}

void Canvas::addElement(std::unique_ptr<UIElement> element) {
    root->addChild(std::move(element));
}

void Canvas::render() const {
    root->render();
}