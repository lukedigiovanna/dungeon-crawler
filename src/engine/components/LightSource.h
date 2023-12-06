#pragma once

#include "Component.h"
#include "../utils/Graphics.h"
#include "../utils/Shader.h"
#include "../utils/Framebuffer.h"

class LightSource: public Component {
    Framebuffer shadowFBO;
public:
    gfx::color color;
    float luminance;
    LightSource(gfx::color const& color, float luminance);

    void set(Shader const& shader, int index) const;

    void update(float dt) override;
};