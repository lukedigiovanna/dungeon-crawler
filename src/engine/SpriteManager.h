#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>

struct Sprite {
    SDL_Texture* texture;
    SDL_Rect rect;
};

class SpriteManager {
private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> textureMap;
    std::unordered_map<std::string, Sprite> spriteMap;
public:
    SpriteManager(SDL_Renderer* renderer);

    void registerSprite(std::string id, std::string spriteSheet, int offX, int offY, int width, int height);
    void registerSprite(std::string id, std::string spritePath);

    const Sprite* getSprite(std::string id) const;

    // Destroys all registered textures
    void destroy();
};