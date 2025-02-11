#pragma once

#include <string>
#include <memory>

#include "../utils/Math.h"
#include "../utils/Shader.h"

// Dictates how the UIElement should respond to changes
// in the screen dimensions.
enum AnchorPreset {
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

// TODO: add cycle detection in UI tree to prevent cycle  bugs which could cause fatal bugs

class UIElement {
private:
    // String to identify the element for access from component scripts.
    std::string tag;
    // Dictates position element should fix itself relative to on screen resize
    math::vec2 anchor;
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
    UIElement* getElementByTag(const std::string& tag);

    // Adds the given element as a child to this element
    void addChild(std::unique_ptr<UIElement> element);

    // Computes the position based on the transform and the screen dimensions
    math::vec2 getComputedPosition() const;

    inline void setTag(const std::string& tag) {
        this->tag = tag;
    }

    inline const std::string getTag() const {
        return tag;
    }

    inline void setAnchor(const math::vec2& anchor) {
        this->anchor = anchor;
    }

    // Compute the anchor based on a preset
    void setAnchor(AnchorPreset anchorPreset);
};