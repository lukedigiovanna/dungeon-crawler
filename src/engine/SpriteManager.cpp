#include "SpriteManager.h"

#include <SDL_image.h>

SpriteManager::SpriteManager(SDL_Renderer* renderer) : renderer(renderer) {

}

void SpriteManager::registerSprite(std::string id, std::string spritePath, int offX, int offY, int width, int height) {
    SDL_Texture* texture;
    auto f = textureMap.find(spritePath);
    if (f == textureMap.end()) {
        texture = IMG_LoadTexture(renderer, spritePath.c_str());
    }
    else {
        texture = f->second;
    }
    textureMap[spritePath] = texture;
    if (spriteMap.find(id) != spriteMap.end()) {
        throw std::runtime_error("SpriteManager::registerSprite: Sprite id '" + id + "' already used");
    }
    spriteMap[id] = {
        texture,
        SDL_Rect{offX, offY, width, height}
    };
}

void SpriteManager::registerSprite(std::string id, std::string spritePath) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, spritePath.c_str());
    if (spriteMap.find(id) != spriteMap.end()) {
        throw std::runtime_error("SpriteManager::registerSprite: Sprite id '" + id + "' already used");
    }
    textureMap[spritePath] = texture;
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    spriteMap[id] = {
        texture,
        SDL_Rect{0, 0, width, height}
    };
}

const Sprite* SpriteManager::getSprite(std::string id) const {
    auto f = spriteMap.find(id);
    if (f == spriteMap.end()) {
        throw std::runtime_error("SpriteManager::getTexture: No sprite in sprite manager with id '" + id + "'");
    }
    return &(f->second);
}

void SpriteManager::destroy() {
    for (const auto & [id, sprite] : spriteMap) {
        SDL_DestroyTexture(sprite.texture);
        spriteMap.erase(id);
    }
}