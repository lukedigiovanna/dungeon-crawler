#include "SpriteManager.h"

#include <stdexcept>

SpriteManager::SpriteManager() {

}

void SpriteManager::registerSpriteSheet(std::string idPrefix, std::string spritePath, int cellsX, int cellsY) {
    if (textureMap.find(spritePath) == textureMap.end()) {
        textureMap[spritePath] = std::make_unique<Texture>(spritePath);
    }
    Texture* texture = textureMap[spritePath].get();
    float cellWidth = 1.0f / cellsX;
    float cellHeight = 1.0f / cellsY;
    int i = 0;
    for (int yi = 0; yi < cellsY; yi++) {
        for (int xi = 0; xi < cellsX; xi++) {
            float y = static_cast<float>(yi) / cellsY;
            float x = static_cast<float>(xi) / cellsX;
            std::string id = idPrefix + std::to_string(i);
            ++i;
            if (spriteMap.find(id) != spriteMap.end()) {
                throw std::runtime_error("SpriteManager::registerSpriteSheet: Sprite id '" + id + "' already used");
            }
            spriteMap[id] = {
                texture,
                { x, y, cellWidth, cellHeight }
            };
        }
    }
}

void SpriteManager::registerSprite(std::string id, std::string spritePath, int offX, int offY, int width, int height) {
    // SDL_Texture* texture;
    // auto f = textureMap.find(spritePath);
    // if (f == textureMap.end()) {
    //     // texture = IMG_LoadTexture(renderer, spritePath.c_str());
    // }
    // else {
    //     texture = f->second;
    // }
    // textureMap[spritePath] = texture;
    // if (spriteMap.find(id) != spriteMap.end()) {
    //     throw std::runtime_error("SpriteManager::registerSprite: Sprite id '" + id + "' already used");
    // }
    // spriteMap[id] = {
    //     // texture,
    //     // SDL_Rect{offX, offY, width, height}
    // };
}

void SpriteManager::registerSprite(std::string id, std::string spritePath) {
    if (spriteMap.find(id) != spriteMap.end()) {
        throw std::runtime_error("SpriteManager::registerSprite: Sprite id '" + id + "' already used");
    }
    if (textureMap.find(spritePath) == textureMap.end()) {
        textureMap[spritePath] = std::make_unique<Texture>(spritePath);
    }
    Texture* texture = textureMap[spritePath].get();
    spriteMap[id] = {
        texture,
        glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}
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
    // for (const auto & [id, sprite] : spriteMap) {
    //     SDL_DestroyTexture(sprite.texture);
    //     spriteMap.erase(id);
    // }
}