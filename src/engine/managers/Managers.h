#pragma once

#include "AnimationManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "SpriteManager.h"

#include <memory>

struct Managers {
private:
    std::unique_ptr<ShaderManager> d_shaderManager;
    std::unique_ptr<SpriteManager> d_spriteManager;
    std::unique_ptr<InputManager> d_inputManager;
    std::unique_ptr<AnimationManager> d_animationManager;
    std::unique_ptr<SceneManager> d_sceneManager;
    std::unique_ptr<FontManager> d_fontManager;

    // std::shared_ptr<SoundManager> soundManager;
    // std::shared_ptr<MusicManager> musicManager;
public:
    Managers();
    
    inline ShaderManager& shaderManager() const {
        return *d_shaderManager;
    }

    inline SpriteManager& spriteManager() const {
        return *d_spriteManager;
    }

    inline InputManager& inputManager() const {
        return *d_inputManager;
    }

    inline AnimationManager& animationManager() const {
        return *d_animationManager;
    }

    inline SceneManager& sceneManager() const {
        return *d_sceneManager;
    }

    inline FontManager& fontManager() const {
        return *d_fontManager;
    }
};
