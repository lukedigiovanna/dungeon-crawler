#pragma once

#include "../managers/SpriteManager.h"

#include <vector>
#include <memory>

class Animation {
private:
    std::vector<const Sprite*> sprites;
    float fps;
public:
    Animation(float fps);

    float getFps() const;

    void addFrame(const Sprite* sprite);
    void addFrame(std::shared_ptr<SpriteManager> spriteManager, std::string const& spriteId);

    const Sprite* getFrame(int frameIndex) const;
    size_t getNumberOfFrames() const;
};