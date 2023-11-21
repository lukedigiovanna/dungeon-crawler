#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>

class SpriteManager {
private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, SDL_Texture*> spriteMap;
public:
    SpriteManager(SDL_Renderer* renderer);

    // void registerTexture(std::string id, std::string spriteSheet, int offX, int offY, int width, int height);
    void registerTexture(std::string id, std::string spritePath);

    SDL_Texture* getTexture(std::string id) const;

    // Destroys all registered textures
    void destroy();
};