#include "Engine.h"

#include "GameObject.h"
#include "components/Camera.h"
#include "components/ComponentOrder.h"
#include "utils/meshes.h"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <algorithm>

#include <glad/glad.h>

Engine::Engine(std::string gameName) {
    window = std::make_unique<Window>(gameName);
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Font::initFreeType();

    font = std::make_unique<Font>("assets/fonts/arial.ttf");

    meshes::init();

    ComponentOrder::initializeEngineDependencies();
    ComponentOrder::updatePriorities();

    managers = std::make_shared<Managers>();

    managers->spriteManager = std::make_shared<SpriteManager>();
    managers->inputManager = std::make_shared<InputManager>();
    managers->animationManager = std::make_shared<AnimationManager>();
    managers->shaderManager = std::make_shared<ShaderManager>();

    managers->shaderManager->loadShader(
        "_scene", 
        "assets/shaders/scene_vs.glsl", "assets/shaders/scene_fs.glsl"
    );

    managers->shaderManager->loadShader(
        "_tm_chunk", 
        "assets/shaders/tm_chunk_vs.glsl", "assets/shaders/tm_chunk_fs.glsl"
    );

    managers->shaderManager->loadShader(
        "_lighting",
        "assets/shaders/light_vs.glsl", "assets/shaders/light_fs.glsl"
    );

    managers->shaderManager->loadShader(
        "_text",
        "assets/shaders/text_vs.glsl", "assets/shaders/text_fs.glsl"
    );

    scene = nullptr;
}

std::shared_ptr<Managers> Engine::getManagers() const {
    return managers;
}

void Engine::loadScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
    this->scene->setManagers(this->managers);
    this->scene->init();
}

void Engine::renderLoop() {
    auto last = std::chrono::system_clock::now();
    while (this->active) {
        auto start = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(start - last);
        last = start;

        float dt = static_cast<float>(elapsed.count()) / 1000000.0f;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->halt();
            }
            this->managers->inputManager->update(event);
        }

        this->scene->update(dt);
        scene->render(window.get());

        Shader& textShader = managers->shaderManager->getShader("_text");
        font->renderText(textShader, "you have small penis syndrome and it is quite unfortunate!", 50, 50, 1);

        SDL_GL_SwapWindow(window->window);

        auto end = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        auto sleepTime = std::chrono::microseconds(1000000 / Engine::TARGET_TPS) - elapsed;
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        }
    }
}

void Engine::run() {
    if (!scene) {
        throw std::runtime_error("Engine::run: Cannot run engine without having a currently loaded scene");
    }
    active = true;
    renderLoop();
}

void Engine::halt() {
    active = false;
}

void Engine::destroy() {
    meshes::destroy();
    std::cout << "destroying engine" << std::endl;
    // spriteManager->destroy();
    std::cout << "destroyed engine" << std::endl;
}

