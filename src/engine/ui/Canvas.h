#pragma once

#include "UIElement.h"

#include <vector>

class Canvas {
private:
    std::unique_ptr<UIElement> root;
public:
    Canvas();

    UIElement* getElementByTag(const std::string& tag) const;

    void addElement(std::unique_ptr<UIElement> element);

    void render() const;
};
