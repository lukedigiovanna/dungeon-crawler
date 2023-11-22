#pragma once

#include "RendererComponent.h"
#include "../../utils/Graphics.h"

enum Shape {
    SQUARE
};

class ShapeRenderer: public RendererComponent {
private:
    Shape shape;
    gfx::color color;
public:
    ShapeRenderer(Shape shape, gfx::color color);
    ~ShapeRenderer();

    void render(Window* window, float x, float y, float width, float height) const override;
};