#include "Engine.h"

#include "GameObject.h"
#include "components/Camera.h"
#include "components/ComponentOrder.h"
#include "utils/meshes.h"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <typeinfo>

#include <glad/glad.h>

const float Engine::FRAME_RESOLUTION = 1.0f / 60.0f;

Engine::Engine(std::string const& gameName) {
    window = std::make_unique<Window>(gameName);
    
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Font::initFreeType();

    meshes::init();

    ComponentOrder::initializeEngineDependencies();
    ComponentOrder::updatePriorities();

    managers = std::make_shared<Managers>();

    ShaderManager& shaderManager = managers->shaderManager();
    shaderManager.loadShader(
        "_scene",
        "assets/shaders/scene_vs.glsl", "assets/shaders/scene_fs.glsl"
    );

    shaderManager.loadShader(
        "_tm_chunk",
        "assets/shaders/tm_chunk_vs.glsl", "assets/shaders/tm_chunk_fs.glsl"
    );

    shaderManager.loadShader(
        "_lighting",
        "assets/shaders/light_vs.glsl", "assets/shaders/light_fs.glsl"
    );

    shaderManager.loadShader(
        "_ui_text",
        "assets/shaders/ui_text_vs.glsl", "assets/shaders/ui_text_fs.glsl"
    );

    shaderManager.loadShader(
        "_ui_sprite",
        "assets/shaders/ui_sprite_vs.glsl", "assets/shaders/ui_sprite_fs.glsl"
    );

    scene = nullptr;
}

void Engine::checkForNewScene() {
    SceneManager& sceneManager = managers->sceneManager();
    if (sceneManager.isDirty()) {
        scene = sceneManager.getCurrentScene();

        if (!scene->isInitialized()) {
            scene->init();
        }

        sceneManager.makeClean();
    }
}

std::shared_ptr<Managers> Engine::getManagers() const {
    return managers;
}

void Engine::renderLoop() {
    checkForNewScene();
    scene->update(0.0f);

    auto last = std::chrono::system_clock::now();
    float accumulator = 0.0f;
    while (this->active) {
        checkForNewScene();

        if (scene == nullptr) {
            throw std::runtime_error("Engine::renderLoop: Scene somehow became null (invalid state)");
        }

        auto start = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(start - last);
        last = start;

        // The real time since last frame
        float dt = static_cast<float>(elapsed.count()) / 1000000.0f;

        accumulator += dt;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->halt();
            }
            managers->inputManager().update(event);
        }

        while (accumulator >= FRAME_RESOLUTION) {
            scene->update(FRAME_RESOLUTION);
            accumulator -= FRAME_RESOLUTION;
        }

        scene->render(window.get());

        SDL_GL_SwapWindow(window->window);        

        auto end = std::chrono::system_clock::now();
        // Sleep for estimated amount of time to stabilize FPS
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        auto sleepTime = std::chrono::microseconds(1000000 / Engine::TARGET_TPS) - elapsed;
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        }
    }
}

void Engine::run() {
    checkForNewScene();

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

std::unique_ptr<Engine> Engine::singleton = nullptr;

Engine* Engine::getSingleton() {
    if (singleton == nullptr) {
        throw std::runtime_error("Engine::getSingleton: Cannot get a singleton of an uninitialized engine!");
    }
    return singleton.get();
}

void Engine::initializeSingleton(std::string const& gameName) {
    singleton = std::make_unique<Engine>(gameName);
}
