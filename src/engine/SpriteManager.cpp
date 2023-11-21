#include "SpriteManager.h"

#include <SDL_image.h>

SpriteManager::SpriteManager(SDL_Renderer* renderer) : renderer(renderer) {

}

void SpriteManager::registerTexture(std::string id, std::string spritePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, spritePath.c_str());
    if (spriteMap.find(id) != spriteMap.end()) {
        throw std::runtime_error("SpriteManager::registerTexture: Sprite id '" + id + "' already used");
    }
    spriteMap[id] = texture;
}

SDL_Texture* SpriteManager::getTexture(std::string id) const {
    auto f = spriteMap.find(id);
    if (f == spriteMap.end()) {
        throw std::runtime_error("SpriteManager::getTexture: No sprite in sprite manager with id '" + id + "'");
    }
    return f->second;
}

void SpriteManager::destroy() {
    for (const auto & [id, texture] : spriteMap) {
        SDL_DestroyTexture(texture);
        spriteMap.erase(id);
    }
}