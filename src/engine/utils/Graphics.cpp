#include "Graphics.h"

#include <cmath>

void gfx::setSDLColor(SDL_Renderer* renderer, gfx::color const& color) {
    SDL_SetRenderDrawColor(
        renderer, 
        static_cast<Uint8>(color.r),
        static_cast<Uint8>(color.g),
        static_cast<Uint8>(color.b),
        static_cast<Uint8>(color.a)
    );
}

void gfx::fillRotatedRectangle(SDL_Renderer* renderer, float x, float y, float width, float height, float angle) {
    float radians = angle / 180.0f * M_PI;
    
}