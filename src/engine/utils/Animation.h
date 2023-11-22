#pragma once

#include <vector>
#include "../managers/SpriteManager.h"

class AnimationSpriteDeck {
private:
    std::vector<const Sprite*> sprites;
public:
    AnimationSpriteDeck();

    void addFrame(const Sprite* sprite);
    void addFrame(std::shared_ptr<SpriteManager> spriteManager, std::string spriteId);
    const Sprite* getFrame(int frameIndex) const;
    size_t getSize() const;
};

class Animation {
private:
    std::shared_ptr<AnimationSpriteDeck> spriteDeck;
    float fps;
    float timer = 0;
    size_t currentFrame = 0;
    bool playing = false;
public:
    Animation(float fps, std::shared_ptr<AnimationSpriteDeck> spriteDeck);

    const Sprite* getCurrentFrame() const;

    void play();
    void update(float dt);
};