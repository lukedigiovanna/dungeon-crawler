#pragma once

#include <SDL.h>

namespace gfx {
struct color {
    float r, g, b, a;
};

static color COLOR_RED = { 255, 0, 0, 255 };
static color COLOR_GREEN = { 0, 255, 0, 255 };
static color COLOR_BLUE = { 0, 0, 255, 255 };

void setSDLColor(SDL_Renderer* renderer, color const& color);
void fillRotatedRectangle(SDL_Renderer* renderer, float x, float y, float width, float height, float angle);
}