#pragma once

#include "../utils/Shader.h"

class UIElement {
public:
    virtual void render(Shader const& uiShader);
};