#include "Managers.h"

Managers::Managers() {
    d_spriteManager = std::make_unique<SpriteManager>();
    d_inputManager = std::make_unique<InputManager>();
    d_animationManager = std::make_unique<AnimationManager>();
    d_shaderManager = std::make_unique<ShaderManager>();
    d_sceneManager = std::make_unique<SceneManager>();
    d_fontManager = std::make_unique<FontManager>();
}
