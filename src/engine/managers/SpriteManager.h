#pragma once

#include "../utils/Sprite.h"
#include "../utils/Texture.h"

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include <SDL.h>
class SpriteManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> textureMap;
    std::vector<Sprite> sprites;
    std::unordered_map<std::string, size_t> spriteMap;
public:
    SpriteManager();
    SpriteManager(const SpriteManager&) = delete;

    void registerSpriteSheet(std::string idPrefix, std::string spriteSheet, int cellsX, int cellsY);
    // void registerSprite(std::string id, std::string spriteSheet, int offX, int offY, int width, int height);
    void registerSprite(std::string id, std::string spritePath);

    const Sprite* getSprite(std::string const& id) const;
    const Sprite* getSpriteByIndex(int id) const;
    int getSpriteIndex(std::string const& id) const;

    size_t getNumSprites() const;

    // Destroys all registered textures
    void destroy();
};