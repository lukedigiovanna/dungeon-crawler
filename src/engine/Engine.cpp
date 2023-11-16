#include "Engine.h"

#include <unistd.h>
#include <iostream>

Engine::Engine(std::string gameName) {
    window = std::make_unique<Window>(gameName);
    scene = std::make_unique<Scene>();
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(); 
    obj->position = { 3, 5};
    scene->addGameObject(obj);
}

void Engine::renderLoop() {
    while (this->active) {
        // Render
        sleep(1);
        std::cout << "Render" << std::endl;
    }
}

void Engine::gameLoop() {
    int counter = 0;
    while (this->active) {
        // Logic
        sleep(1);
        std::cout << "Logic " << counter++ << std::endl;

        if (counter >= 5) {
            this->halt();
        }
    }
}

void Engine::start() {
    // spin up the thred instances
    renderThread = std::make_unique<std::thread>(&Engine::renderLoop, this);
    gameThread = std::make_unique<std::thread>(&Engine::gameLoop, this);
    active = true;
}

void Engine::halt() {
    active = false;
}

void Engine::join() {
    renderThread->join();
    gameThread->join();
}

