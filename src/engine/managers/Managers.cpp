#include "Managers.h"

Managers::Managers() {
    spriteManager = std::make_shared<SpriteManager>();
    inputManager = std::make_shared<InputManager>();
    animationManager = std::make_shared<AnimationManager>();
    shaderManager = std::make_shared<ShaderManager>();
    sceneManager = std::make_shared<SceneManager>();
}