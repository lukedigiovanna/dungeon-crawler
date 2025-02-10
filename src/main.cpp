#define _USE_MATH_DEFINES

#define STB_IMAGE_IMPLEMENTATION
#include "engine/stb_image.h"

#include <SDL.h>
#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <iostream>
#include <memory>
#include <array>
#include <string>

#include "engine/Engine.h"
#include "engine/Scene.h"
#include "game/scenes.h"
#include "engine/utils/Math.h"
#include "engine/components/ComponentOrder.h"
#include "engine/components/Collider.h"
#include "engine/components/SpriteAnimator.h"
#include "game/components/PlayerMovement.h"

int program() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // For example, OpenGL 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    ComponentOrder::addDependency<PlayerMovement, Physics>();
    ComponentOrder::addDependency<PlayerMovement, SpriteAnimator>();

    Engine::initializeSingleton("cool game");

    Engine* engine = Engine::getSingleton();

    std::shared_ptr<Managers> managers = engine->getManagers();

    FontManager& fontManager = managers->fontManager();
    fontManager.registerFont("minecraft", "assets/fonts/Minecraft.ttf");
    fontManager.registerFont("arial", "assets/fonts/arial.ttf");

    SpriteManager& spriteManager = managers->spriteManager();
    spriteManager.registerSprite("smile", "assets/smile.png");
    int nf = 12;
    std::array<std::string, 4> dirs = {"down", "left", "right", "up"};
    spriteManager.registerSpriteSheet("character", "assets/character3.png", nf, 4);
    // int nf = 9;
    // std::array<std::string, 4> dirs = {"up", "left", "down", "right"};
    // spriteManager->registerSpriteSheet("character", "assets/character2.png", nf, 4);
    // int nf = 4;
    // std::array<std::string, 4> dirs = {"down", "right", "left", "up"};
    // spriteManager->registerSpriteSheet("character", "assets/character.png", nf, 4);

    spriteManager.registerSpriteSheet("minecraft", "assets/minecraft.png", 24, 34);
    spriteManager.registerSprite("background", "assets/topdown.png");
    
    AnimationManager& animationManager = engine->getManagers()->animationManager();
    
    int walkIndex = 0;
    for (std::string const& dir : dirs) {
        std::shared_ptr<Animation> ani = std::make_shared<Animation>(14.0f);
        for (int i = 0; i < nf; i++) {
            ani->addFrame(managers->spriteManager().getSprite("character" + std::to_string(walkIndex++)));
        }
        managers->animationManager().registerAnimation("player-walk-" + dir, ani);
    }

    std::shared_ptr<Animation> minecraftAnimation = std::make_shared<Animation>(20.0f);
    for (int i = 0; i < 800; i++) {
        minecraftAnimation->addFrame(spriteManager.getSprite("minecraft" + std::to_string(i)));
    }
    animationManager.registerAnimation("minecraft", minecraftAnimation);
    std::shared_ptr<Animation> wheatGrow = std::make_shared<Animation>(2.0f);
    for (int i = 128; i < 136; i++) {
        wheatGrow->addFrame(spriteManager.getSprite("minecraft" + std::to_string(i)));
    }
    animationManager.registerAnimation("wheat-grow", wheatGrow);

    std::shared_ptr<Scene> mainMenuScene = std::make_shared<scenes::MainMenuScene>();
    std::shared_ptr<Scene> sampleScene = std::make_shared<scenes::SampleScene>();
    managers->sceneManager().registerScene("sample", sampleScene);
    managers->sceneManager().registerScene("main_menu", mainMenuScene);

    managers->sceneManager().loadScene("main_menu");

    engine->run();

    engine->destroy();

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
    
