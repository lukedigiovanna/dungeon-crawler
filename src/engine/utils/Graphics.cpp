#include "Graphics.h"

void gfx::setSDLColor(SDL_Renderer* renderer, gfx::color const& color) {
    SDL_SetRenderDrawColor(
        renderer, 
        static_cast<Uint8>(color.r),
        static_cast<Uint8>(color.g),
        static_cast<Uint8>(color.b),
        static_cast<Uint8>(color.a)
    );
}