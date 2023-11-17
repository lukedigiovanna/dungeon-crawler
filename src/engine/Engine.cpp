#include "Engine.h"
#include "components/Camera.h"
#include "GameObject.h"

#include <unistd.h>
#include <iostream>
#include <chrono>
#include <algorithm>

Engine::Engine(std::string gameName) {
    window = std::make_unique<Window>(gameName);
    scene = std::make_unique<Scene>();
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(); 
    obj->position = { 3, 5 };
    std::shared_ptr<Camera> camera = std::make_shared<Camera>();
    obj->addComponent(camera);
    std::shared_ptr<Camera> retrievedCam = obj->getComponent<Camera>();
    std::cout << retrievedCam->zoomScale << std::endl;
    scene->addGameObject(obj);
}

void Engine::renderLoop() {
    while (this->active) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->halt();
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255); // black
        SDL_RenderClear(window->renderer);

        // Draw a rectangle
        SDL_Rect rect = { 250, 190, 140, 100 };
        SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255); // red
        SDL_RenderFillRect(window->renderer, &rect);

        SDL_RenderPresent(window->renderer);
    }
}

void Engine::gameLoop() {
    auto last = std::chrono::system_clock::now();
    while (this->active) {
        auto start = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(start - last);
        last = start;

        float dt = static_cast<float>(elapsed.count()) / 1000000.0f;

        // #### START LOGIC ####

        std::cout << dt << std::endl;

        // #### END LOGIC ####
        
        auto sleepTime = std::chrono::microseconds(1000000 / Engine::TARGET_TPS);
        if (sleepTime.count() > 0) {
            std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
        }
    }
}

void Engine::run() {
    // spin up the thred instances
    gameThread = std::make_unique<std::thread>(&Engine::gameLoop, this);
    active = true;
    renderLoop();
    gameThread->join();
}

void Engine::halt() {
    active = false;
}

