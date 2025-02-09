#pragma once

#include "Component.h"
#include "../utils/Light.h"
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
    Light light;
    bool castsShadow;

    LightSource(const gfx::color& color, float luminance, bool castsShadow);

    void set(Shader const& shader, int index, glm::mat4 const& projection) const;

    void update(float dt) override;
};