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
            Sprite s{
                texture,
                glm::vec4{ x, y, cellWidth, cellHeight }
            };
            spriteMap[id] = sprites.size();
            sprites.push_back(s);
        }
    }
}

void SpriteManager::registerSprite(std::string id, std::string spritePath) {
    if (spriteMap.find(id) != spriteMap.end()) {
        throw std::runtime_error("SpriteManager::registerSprite: Sprite id '" + id + "' already used");
    }
    if (textureMap.find(spritePath) == textureMap.end()) {
        textureMap[spritePath] = std::make_unique<Texture>(spritePath);
    }
    Texture* texture = textureMap[spritePath].get();
    Sprite s{
        texture,
        glm::vec4{0.0f, 0.0f, 1.0f, 1.0f}
    };
    spriteMap[id] = sprites.size();
    sprites.push_back(s);
}

const Sprite* SpriteManager::getSprite(std::string const& id) const {
    auto f = spriteMap.find(id);
    if (f == spriteMap.end()) {
        throw std::runtime_error("SpriteManager::getTexture: No sprite in sprite manager with id '" + id + "'");
    }
    return &sprites[f->second];
}

const Sprite* SpriteManager::getSpriteByIndex(int index) const {
    if (index < 0 || index >= sprites.size()) {
        throw std::runtime_error("SpriteManager::getSprie: Index out of range: " + std::to_string(index));
    }
    return &sprites[index];
}

int SpriteManager::getSpriteIndex(std::string const& id) const {
    auto f = spriteMap.find(id);
    if (f == spriteMap.end()) {
        throw std::runtime_error("SpriteManager::getSpriteIndex: No sprite in sprite manager with id '" + id + "'");
    }
    return f->second;
}

size_t SpriteManager::getNumSprites() const {
    return sprites.size();
}

void SpriteManager::destroy() {
    // for (const auto & [id, sprite] : spriteMap) {
    //     SDL_DestroyTexture(sprite.texture);
    //     spriteMap.erase(id);
    // }
}