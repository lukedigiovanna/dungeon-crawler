#pragma once

#include "Math.h"

struct Wall {
    math::LineSegment line;
    bool physical;
    float occlusionFactor; // 0 => transparent, 1.0 => opaque

    bool intersects(Wall const& wall);
};
