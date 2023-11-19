#pragma once

#include "Scene.h"
#include "graphics/Window.h"

#include <memory>
#include <thread>
#include <atomic>

class Engine {
private:
    std::unique_ptr<Window> window;
    std::shared_ptr<Scene> scene;    

    std::unique_ptr<std::thread> gameThread;

    std::atomic<bool> active;
public:
    static const unsigned int TARGET_TPS = 20;

    Engine(std::string gameName);

    // Initiates a render thread and a logic thread
    void run();
    void halt();

    void renderLoop();
    void gameLoop();
};