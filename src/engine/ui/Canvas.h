#pragma once

#include "UIElement.h"

#include <vector>

class Canvas {
private:
    std::unique_ptr<UIElement> root;
public:
    Canvas();

    UIElement* getElementById(const std::string& id) const;

    void addElement(std::unique_ptr<UIElement> element);

    void render() const;
};
