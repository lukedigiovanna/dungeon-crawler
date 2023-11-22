#define _USE_MATH_DEFINES

#include <SDL.h>
#include <iostream>
#include <memory>

#include "engine/Engine.h"
#include "engine/Scene.h"
#include "game/scenes.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Engine engine("Cool");
    
    std::shared_ptr<SpriteManager> spriteManager = engine.getManagers()->spriteManager;
    spriteManager->registerSprite("smile", "assets/smile.png");
    spriteManager->registerSprite("cat", "assets/image.jpeg");
    spriteManager->registerSpriteSheet("character", "assets/character.png", 4, 4);
    spriteManager->registerSpriteSheet("minecraft", "assets/minecraft.png", 24, 34);
    
    std::shared_ptr<AnimationManager> animationManager = engine.getManagers()->animationManager;
    std::shared_ptr<AnimationSpriteDeck> walkAnimation = std::make_shared<AnimationSpriteDeck>();
    walkAnimation->addFrame(spriteManager, "character0");
    walkAnimation->addFrame(spriteManager, "character1");
    walkAnimation->addFrame(spriteManager, "character2");
    walkAnimation->addFrame(spriteManager, "character3");
    animationManager->registerAnimation("player-walk", walkAnimation);

    std::shared_ptr<Scene> startingScene = std::make_shared<scenes::SampleScene>();
    engine.loadScene(startingScene);

    engine.run();
    engine.destroy();

    SDL_Quit();
    return 0;
}
