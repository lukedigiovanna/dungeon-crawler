#pragma once

#include "../utils/Sprite.h"
#include "../utils/Texture.h"

#include <string>
#include <unordered_map>
#include <memory>

#include <SDL.h>

class SpriteManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> textureMap;
    std::unordered_map<std::string, Sprite> spriteMap;
public:
    SpriteManager();

    void registerSpriteSheet(std::string idPrefix, std::string spriteSheet, int cellsX, int cellsY);
    void registerSprite(std::string id, std::string spriteSheet, int offX, int offY, int width, int height);
    void registerSprite(std::string id, std::string spritePath);

    const Sprite* getSprite(std::string id) const;

    // Destroys all registered textures
    void destroy();
};