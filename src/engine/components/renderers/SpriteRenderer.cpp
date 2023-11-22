#include "SpriteRenderer.h"

#include "../../GameObject.h"
#include "../../Scene.h"
#include "../../utils/Math.h"
#include "../../managers/Managers.h"

#include <SDL_image.h>
#include <cmath>

SpriteRenderer::SpriteRenderer(std::string spriteId) : spriteId(spriteId) {

}

void SpriteRenderer::init() {
    std::shared_ptr<SpriteManager> spriteManager = this->getGameObject()->getScene()->getManagers()->spriteManager;
    this->sprite = spriteManager->getSprite(spriteId);
}

void SpriteRenderer::render(Window* window, float x, float y, float width, float height) const {
    std::shared_ptr<GameObject> obj = this->getGameObject();
    SDL_FRect dstrect = { x - width / 2.0f, y - height / 2.0f, width, height };
    SDL_RenderCopyExF(window->renderer, sprite->texture, &sprite->rect, &dstrect, obj->rotation, NULL, SDL_FLIP_NONE);
}