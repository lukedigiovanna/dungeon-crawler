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
    
    std::shared_ptr<Scene> startingScene = std::make_shared<scenes::SampleScene>();
    engine.loadScene(startingScene);
    
    std::shared_ptr<SpriteManager> spriteManager = engine.getSpriteManager();
    spriteManager->registerSprite("smile", "assets/smile.png");
    spriteManager->registerSprite("cat", "assets/image.jpeg");
    spriteManager->registerSprite("character0", "assets/character.png", 0, 0, 200, 200);
    spriteManager->registerSprite("character1", "assets/character.png", 50, 50, 50, 50);
    
    engine.run();
    engine.destroy();

    SDL_Quit();
    return 0;
}
