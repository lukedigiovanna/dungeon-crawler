#include "UIElement.h"

#include "../Engine.h"
#include "../Window.h"

UIElement::UIElement() : UIElement(0, 0) {

}

UIElement::UIElement(float x, float y) :
    transform{math::vec2{x, y}, math::vec2{1, 1}, 0},
    scaleMode(ScaleMode::SCALE_CONSTANT),
    anchor(Anchor::ANCHOR_TOP_LEFT),
    tag("untagged"),
    parent(nullptr),
    alignment(PositionAlignment::POSITION_CENTER),
    active(true) {

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

void UIElement::recomputeDimension() {
    // Note: dependent on this elements scale mode and the ratio of
    //       the parent's representational dimension to their computed dimension
    if (!parent) {
        const Window* window = Engine::getSingleton()->getWindow();
        computedDimension = { window->width(), window->height() };
        return;
    }
    if (scaleMode == ScaleMode::SCALE_CONSTANT) {
        computedDimension = transform.scale;
        return;
    }

    math::vec2 p_representational = parent->transform.scale;
    math::vec2 p_computed = parent->getComputedDimension();

    // Note: maintains the aspect ratio
    float scaleFactor; 
    if (scaleMode == ScaleMode::SCALE_WITH_WIDTH) {
        scaleFactor = p_computed.x / p_representational.x;
    }
    else if (scaleMode == ScaleMode::SCALE_WITH_HEIGHT) {
        scaleFactor = p_computed.y / p_representational.y;
    }
    computedDimension = transform.scale * scaleFactor;
}

void UIElement::recomputeAnchor() {
    // Note: for anchors (0, 0) always denotes the top-left position
    //       of the parent. So (0, 0) is *always* the top-left anchor coordinate.
    //       the anchor position is merely dependent on the size of the parent.
    math::vec2 dimension;
    if (parent) {
        dimension = parent->transform.scale;
    }
    else {
        dimension = { Window::DEFAULT_WIDTH, Window::DEFAULT_HEIGHT };
    }
    switch (anchor) {
    case Anchor::ANCHOR_TOP_LEFT:
        anchorPosition = { 0.0f, 0.0f }; break;
    case Anchor::ANCHOR_TOP_CENTER:
        anchorPosition = { dimension.x / 2.0f, 0.0f }; break;
    case Anchor::ANCHOR_TOP_RIGHT:
        anchorPosition = { dimension.x, 0.0f }; break;
    case Anchor::ANCHOR_CENTER_LEFT:
        anchorPosition = { 0.0f, dimension.y / 2.0f }; break;
    case Anchor::ANCHOR_CENTER:
        anchorPosition = { dimension.x / 2.0f, dimension.y / 2.0f }; break;
    case Anchor::ANCHOR_CENTER_RIGHT:
        anchorPosition = { dimension.x, dimension.y / 2.0f }; break;
    case Anchor::ANCHOR_BOTTOM_LEFT:
        anchorPosition = { 0.0f, dimension.y }; break;
    case Anchor::ANCHOR_BOTTOM_CENTER:
        anchorPosition = { dimension.x / 2.0f, dimension.y }; break;
    case Anchor::ANCHOR_BOTTOM_RIGHT:
        anchorPosition = { dimension.x, dimension.y }; break;
    }
}

void UIElement::recomputePosition() {
    math::vec2 p_position;
    math::vec2 p_dimension;
    math::vec2 p_dimensionComputed;
    if (parent) {
        p_position = parent->getComputedPosition();
        p_dimension = parent->transform.scale;
        p_dimensionComputed = parent->getComputedDimension();
    }
    else {
        const Window* window = Engine::getSingleton()->getWindow();
        p_position = { 0, 0 };
        p_dimension = { Window::DEFAULT_WIDTH, Window::DEFAULT_HEIGHT };
        p_dimensionComputed = { window->width(), window->height() };
    }
    math::vec2 computedAnchorPosition = {
        anchorPosition.x / p_dimension.x * p_dimensionComputed.x,
        anchorPosition.y / p_dimension.y * p_dimensionComputed.y
    };
    math::vec2 relativeOffset = transform.position - anchorPosition;
    computedPosition = p_position + computedAnchorPosition + relativeOffset;
    if (alignment == PositionAlignment::POSITION_CENTER) {
        computedPosition -= computedDimension / 2;
    }
}

void UIElement::recomputePositionAndDimension() {
    recomputeDimension();
    recomputeAnchor();
    recomputePosition();
    // std::cout << "t: " << tag 
    //           << " a: " << "(" << anchorPosition.x <<  ", " << anchorPosition.y << ")"
    //           << " cd: " << "(" << computedDimension.x <<  ", " << computedDimension.y << ")" 
    //           << " cp: " << "(" << computedPosition.x <<  ", " << computedPosition.y << ")"
    //           << " d: " << "(" << transform.scale.x <<  ", " << transform.scale.y << ")" 
    //           << " p: " << "(" << transform.position.x <<  ", " << transform.position.y << ")" << std::endl;
    for (const auto& child : children) {
        child->recomputePositionAndDimension();
    }
}

void UIElement::renderElement() const {

}

void UIElement::render() const {
    if (!active) {
        return;
    }

    // std::cout << this->tag << std::endl;

    renderElement();

    for (const auto& child : children) {
        child->render();
    }
}