#pragma once

#include "Component.h"
#include "../utils/Graphics.h"
#include "../utils/Shader.h"
#include "../utils/Framebuffer.h"

class LightSource: public Component {
private:
    static void initializeVertexObject();
    static unsigned int vbo;
    static unsigned int vao;
    static bool initialized;
public:
    Framebuffer shadowFBO;
    gfx::color color;
    float luminance;
    LightSource(const gfx::color& color, float luminance);

    void set(Shader const& shader, int index, glm::mat4 const& projection) const;

    void update(float dt) override;
};