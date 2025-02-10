#pragma once

#include <string>
#include <memory>

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
private:
    // Optional string to identify the element for access from component scripts.
    std::string id;
    // Dictates position element should fix itself relative to on screen resize
    Anchor anchor;
    // Child elements
    std::vector<std::unique_ptr<UIElement>> children;
    // Reference to the parent, if it has one
    const UIElement* parent;
public:
    // Position relative to the parent in dimensions of the default screen size.
    math::Transform transform;

    UIElement();
    UIElement(float x, float y);

    virtual void render() const;

    // Performs a DFS on the canvas tree for the element with the given ID.
    UIElement* getElementById(const std::string& id);

    void addChild(std::unique_ptr<UIElement> element);

    inline void setID(const std::string& id) {
        this->id = id;
    }

    inline const std::string getID() const {
        return id;
    }
};