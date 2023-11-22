#include "Engine.h"
#include "components/Camera.h"
#include "GameObject.h"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <algorithm>

Engine::Engine(std::string gameName) {
    window = std::make_unique<Window>(gameName);
    managers.spriteManager = std::make_shared<SpriteManager>(window->renderer);
    managers.inputManager = std::make_shared<InputManager>();
    managers.animationManager = std::make_shared<AnimationManager>();
    scene = nullptr;
}

const Managers* Engine::getManagers() const {
    return &(this->managers);
}

void Engine::loadScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
    this->scene->setManagers(&this->managers);
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
            this->managers.inputManager->update(event);
        }

        this->scene->update(dt);
        scene->render(window.get());

        SDL_RenderPresent(window->renderer);

        auto end = std::chrono::system_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        auto sleepTime = std::chrono::microseconds(1000000 / Engine::TARGET_TPS) - elapsed;
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        }
    }
}

void Engine::gameLoop() {
    // auto last = std::chrono::system_clock::now();
    // while (this->active) {
    //     auto start = std::chrono::system_clock::now();
    //     auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(start - last);
    //     last = start;

    //     float dt = static_cast<float>(elapsed.count()) / 1000000.0f;

    //     // #### START LOGIC ####

    //     std::cout << dt << std::endl;
    //     this->scene->update(dt);
    //     std::cout << dt << std::endl;

    //     // #### END LOGIC ####
        
    //     auto sleepTime = std::chrono::microseconds(1000000 / Engine::TARGET_TPS);
    //     if (sleepTime.count() > 0) {
    //         std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
    //     }
    // }
}

void Engine::run() {
    if (!scene) {
        throw std::runtime_error("Engine::run: Cannot run engine without having a currently loaded scene");
    }
    // spin up the thread instances
    active = true;
    // gameThread = std::make_unique<std::thread>(&Engine::gameLoop, this);
    renderLoop();
    // gameThread->join();
}

void Engine::halt() {
    active = false;
}

void Engine::destroy() {
    std::cout << "destroying engine" << std::endl;
    // spriteManager->destroy();
    std::cout << "destroyed engine" << std::endl;
}

