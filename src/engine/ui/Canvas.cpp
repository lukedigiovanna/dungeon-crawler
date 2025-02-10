#include "Canvas.h"

Canvas::Canvas() {
    root = std::make_unique<UIElement>();
}

UIElement* Canvas::getElementById(const std::string& id) const {
    return root->getElementById(id);
}

void Canvas::addElement(std::unique_ptr<UIElement> element) {
    root->addChild(std::move(element));
}

void Canvas::render() const {
    root->render();
}