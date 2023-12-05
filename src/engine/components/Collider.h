#pragma once

#include "Component.h"
#include "../utils/Math.h"

#include <array>

class Collider: public Component {
private:
    math::Polygon polygon;
    math::Transform transform;
    void regeneratePolygon();
public:
    Collider();

    void init() override;
    void update(float dt) override;
};