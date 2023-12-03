#pragma once

#include "Component.h"
#include "../utils/Graphics.h"

class LightSource: public Component {
public:
    gfx::color color;
    float luminance;
    LightSource(gfx::color const& color, float luminance);
};