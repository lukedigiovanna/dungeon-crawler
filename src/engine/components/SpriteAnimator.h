#pragma once

#include "Component.h"
#include "renderers/SpriteRenderer.h"
#include "../utils/Animation.h"

#include <functional>

enum AnimatorLoopType {
    LOOP_ONCE,
    LOOP_CONTINUOUSLY
};

class SpriteAnimator: public Component {
private:
    std::string animationId;
    std::shared_ptr<Animation> animation;
    SpriteRenderer* spriteRenderer;
    bool initialized;

    AnimatorLoopType loopType;
    bool shouldPlay = false;
    std::function<void()> loopOnceCallbackFunction;

    float timer = 0.0f;
    int currentFrame = 0;

public:
    float speedScale = 1.0f;
    
public:
    SpriteAnimator(std::string const& animationId);

    void setAnimation(std::string const& animationId);

    void seek(float timeOffset);

    void stop();
    void pause();
    void resume();
    void reset();
    void loop();
    void loopOnce();
    void loopOnce(std::function<void()> callback);

    void init() override;
    void update(float dt) override;
};