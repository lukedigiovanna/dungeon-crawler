#pragma once

#include "SpriteManager.h"
#include "InputManager.h"
#include "AnimationManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"

#include <memory>

struct Managers {
    Managers();

    std::shared_ptr<ShaderManager> shaderManager;
    std::shared_ptr<SpriteManager> spriteManager;
    std::shared_ptr<InputManager> inputManager;
    std::shared_ptr<AnimationManager> animationManager;
    std::shared_ptr<SceneManager> sceneManager;
    // std::shared_ptr<SoundManager> soundManager;
    // std::shared_ptr<MusicManager> musicManager;
};