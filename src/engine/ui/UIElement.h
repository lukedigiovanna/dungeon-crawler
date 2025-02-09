#pragma once

#include <string>

#include "../utils/Math.h"
#include "../utils/Shader.h"

// Dictates how the UIElement should respond to changes
// in the screen dimensions.
enum Anchor {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
};

class UIElement {
public:
    // String to identify the element for access from component scripts.
    std::string tag;
    // Dictates position element should fix itself relative to on screen resize
    Anchor anchor;
    // Position relative to the parent in dimensions of the default screen size.
    math::Transform transform;
    // Child elements
    std::vector<std::unique_ptr<UIElement>> children;
    // Reference to the parent, if it has one
    std::weak_ptr<UIElement> parent;

    virtual void render(Shader const& uiShader);
};