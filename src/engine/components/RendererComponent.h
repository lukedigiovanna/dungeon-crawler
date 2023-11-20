#pragma once

#include "../Window.h"

class RendererComponent {
private:
public:
    RendererComponent();

    virtual void render(Window* window, float x, float y, float width, float height) const;
};