#include "SpriteRenderer.h"

#include <SDL_image.h>

#include <cmath>
#include "../utils/Math.h"
#include "../GameObject.h"
#include "../SpriteManager.h"
#include "../Scene.h"

SpriteRenderer::SpriteRenderer(std::string spriteId) : spriteId(spriteId) {

}

void SpriteRenderer::init() {
    std::shared_ptr<SpriteManager> spriteManager = this->getGameObject()->getScene()->getSpriteManager();
    this->texture = spriteManager->getTexture(spriteId);
}

void SpriteRenderer::render(Window* window, float x, float y, float width, float height) const {
    SDL_FRect dstrect = { x - width / 2.0f, y - height / 2.0f, width, height };
    std::shared_ptr<GameObject> obj = this->getGameObject();
    SDL_RenderCopyExF(window->renderer, texture, NULL, &dstrect, obj->rotation, NULL, SDL_FLIP_NONE);
}