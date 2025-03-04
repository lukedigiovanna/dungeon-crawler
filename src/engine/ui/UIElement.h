#pragma once

#include <string>
#include <memory>

#include "../utils/Math.h"
#include "../utils/Shader.h"

// Dictates how the UIElement should respond to changes
// in the screen dimensions.
enum Anchor {
    ANCHOR_TOP_LEFT,
    ANCHOR_TOP_CENTER,
    ANCHOR_TOP_RIGHT,
    ANCHOR_CENTER_LEFT,
    ANCHOR_CENTER,
    ANCHOR_CENTER_RIGHT,
    ANCHOR_BOTTOM_LEFT,
    ANCHOR_BOTTOM_CENTER,
    ANCHOR_BOTTOM_RIGHT,
};

enum ScaleMode {
    SCALE_CONSTANT, // No scaling with screen size change
    SCALE_WITH_WIDTH, // Match the width scaling factor
    SCALE_WITH_HEIGHT, // Match the height scaling factor
};

enum PositionAlignment {
    POSITION_CENTER,
    POSITION_TOP_LEFT,
};

// TODO: add cycle detection in UI tree to prevent cycle  bugs which could cause fatal bugs

class UIElement {
private:
    // String to identify the element for access from component scripts.
    std::string tag;
    
    // Dictates position element should fix itself relative to on screen resize
    Anchor anchor;
    math::vec2 anchorPosition;

    // Dictates how the scale of the element should change with screen size changes
    // implementation is dependent on the element type
    ScaleMode scaleMode;

    PositionAlignment alignment;

    // Child elements
    std::vector<std::unique_ptr<UIElement>> children;

    // Reference to the parent, if it has one
    const UIElement* parent;

    math::vec2 computedDimension;
    math::vec2 computedAnchorPosition;
    math::vec2 computedPosition;
public:
    // Position relative to the parent in dimensions of the default screen size.
    // By convention, the position should always be the top-left position of the element.
    // The dimension extends down and right
    math::Transform transform;

    UIElement();
    UIElement(float x, float y);

    virtual void render() const;

    // Performs a DFS on the canvas tree for the first element with the given ID.
    UIElement* getElementByTag(const std::string& tag);

    // Adds the given element as a child to this element
    void addChild(std::unique_ptr<UIElement> element);

    // Should be performed before render.
    // Will also update the position and dimension of any child elements.
    void recomputePositionAndDimension();
private:
    void recomputeDimension();
    void recomputeAnchor();
    void recomputePosition();
public:
// inline methods
    inline const math::vec2& getComputedPosition() const {
        return this->computedPosition;
    }

    inline const math::vec2& getComputedDimension() const {
        return this->computedDimension;
    }

    inline void setTag(const std::string& tag) {
        this->tag = tag;
    }

    inline const std::string getTag() const {
        return tag;
    }

    inline void setAnchor(Anchor anchor) {
        this->anchor = anchor;
    }

    inline void setScaleMode(ScaleMode scaleMode) {
        this->scaleMode = scaleMode;
    }

    inline void setAlignment(PositionAlignment alignment) {
        this->alignment = alignment;
    }

    inline ScaleMode getScaleMode() const {
        return scaleMode;
    }

    inline PositionAlignment getAlignment() const {
        return alignment;
    }
};