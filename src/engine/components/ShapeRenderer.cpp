#include "ShapeRenderer.h"

#include <iostream>

ShapeRenderer::ShapeRenderer(Shape shape, gfx::color color) : shape(shape), color(color) {

}

void ShapeRenderer::render(Window* window, float x, float y, float width, float height) const {
    gfx::setSDLColor(window->renderer, this->color);
    SDL_FRect rect = { x - width / 2, y - height / 2, width, height };
    SDL_RenderFillRectF(window->renderer, &rect);
}