#pragma once

#include "Component.h"
#include "../utils/Math.h"

#include <array>

class Collider: public Component {
private:
    std::array<LineSegment, 4> diagonals;
    vec2 diagPos{0, 0};
    vec2 diagScale{1, 1};
    float diagRotation = 0;
    void regenerateDiagonals();
public:
    Collider();

    void init() override;
    void update(float dt) override;
};