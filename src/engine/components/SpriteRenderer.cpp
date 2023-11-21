#include "SpriteRenderer.h"

#include <SDL_image.h>

#include <cmath>
#include "../utils/Math.h"
#include "../GameObject.h"

SpriteRenderer::SpriteRenderer() {
}

void SpriteRenderer::render(Window* window, float x, float y, float width, float height) const {
    SDL_Texture* mTexture = IMG_LoadTexture(window->renderer, "assets/image.jpeg");
    SDL_FRect dstrect = { x - width / 2.0f, y - height / 2.0f, width, height };
    std::shared_ptr<GameObject> obj = this->getGameObject();
    float radians = obj->rotation;
    SDL_RenderCopyExF(window->renderer, mTexture, NULL, &dstrect, radians, NULL, SDL_FLIP_NONE);
}