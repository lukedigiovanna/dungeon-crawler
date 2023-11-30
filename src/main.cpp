#define _USE_MATH_DEFINES

#define STB_IMAGE_IMPLEMENTATION
#include "engine/stb_image.h"

#include <SDL.h>
#include <iostream>
#include <memory>
#include <glad/glad.h>

#include "engine/Engine.h"
#include "engine/Scene.h"
#include "game/scenes.h"

int program() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // For example, OpenGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    Engine engine("Cool");
    
    std::shared_ptr<SpriteManager> spriteManager = engine.getManagers()->spriteManager;
    spriteManager->registerSprite("smile", "assets/smile.png");
    spriteManager->registerSprite("cat", "assets/minecraft.png");
    // spriteManager->registerSpriteSheet("character", "assets/character.png", 4, 4);
    spriteManager->registerSpriteSheet("minecraft", "assets/minecraft.png", 24, 34);
    spriteManager->registerSprite("background", "assets/topdown.png");
    
    // std::shared_ptr<AnimationManager> animationManager = engine.getManagers()->animationManager;
    // std::shared_ptr<AnimationSpriteDeck> walkAnimation = std::make_shared<AnimationSpriteDeck>();
    // walkAnimation->addFrame(spriteManager, "character0");
    // walkAnimation->addFrame(spriteManager, "character1");
    // walkAnimation->addFrame(spriteManager, "character2");
    // walkAnimation->addFrame(spriteManager, "character3");
    // animationManager->registerAnimation("player-walk", walkAnimation);

    std::shared_ptr<Scene> startingScene = std::make_shared<scenes::SampleScene>();
    engine.loadScene(startingScene);

    engine.run();
    engine.destroy();

    SDL_Quit();

    return 0;
}

#ifdef _WIN32
    #include <windows.h>
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
        return program();
    }
#else
    int main(int argc, char* argv[]) {
        return program();
    }
#endif
    
